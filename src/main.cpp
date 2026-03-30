/**
 *@file RadarScanner
 *@author Daniel Pelzel
 *@brief measure Distance with HC-SR04 and Servo SG90 control
 */


#include <Arduino.h>
#include <Servo.h>

/**
 * @brief Represents a servo motor instance.
 *
 * This instance is used to control a servo motor. You can attach the servo
 * to a specific pin, define its movement range, and send commands to control
 * its position using various methods such as `write` or `writeMicroseconds`.
 *
 * The servo motor can be attached to a pin using the `attach` method, which
 * initializes the required pin and sets constraints for operations. To move
 * the servo, you may use the `write` method to control the angle or use
 * `writeMicroseconds` for precise pulse width control.
 */
Servo servo;

const uint8_t trig = 8; /**
 * @brief Pin number for the ultrasonic sensor's "Trig" signal.
 *
 * This pin is used as an output to send a trigger signal to the ultrasonic sensor.
 * The trigger signal prompts the sensor to emit an ultrasonic pulse.
 */
const uint8_t echo = 7; /**
 * @brief Pin connected to the servo motor signal line.
 *
 * This constant defines the pin number used to control the servo motor.
 * It should be configured as an OUTPUT pin in the setup function.
 * The value corresponds to the digital pin on the microcontroller.
 */
const uint8_t servo_pin = 9; ///< PWN-Signal for SG90 Servo


/**
 * @brief Measures the distance to an object using an ultrasonic sensor.
 *
 * This function sends an ultrasonic pulse via the `trig` pin and measures
 * the time taken for the echo to return using the `echo` pin. It calculates
 * the distance to the object based on the speed of sound and returns the distance
 * in centimeters.
 *
 * @return The calculated distance to the object in centimeters.
 *
 * @note The speed of sound is assumed to be 340 m/s. Ensure the `trig` and `echo`
 *       pins are configured correctly before invoking this function.
 */
float measure_distance() {

    // Sicherstellen, dass der Pin vorher LOW ist
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    //Sending Input signal (10 microseconds)
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    //ultrasonic wave time
    float seconds = pulseIn(echo, HIGH) * 1e-6;

    //time to distance calc.
    float distance_m = (seconds * 340.0 /2.0);
    float distance_cm = distance_m * 100;

    return distance_cm;
}

/**
 * @brief Sends data over the serial connection.
 *
 * This function sends the specified angle and distance as a comma-separated
 * pair over the serial connection for external monitoring or debugging.
 * The angle is displayed as an integer, and the distance is displayed
 * as a floating-point value.
 *
 * @param angle The angle of the servo motor in degrees.
 * @param distance The measured distance in centimeters.
 */
void sendData(int angle, float distance) {
    Serial.print(angle);
    Serial.print(", ");
    Serial.println(distance);
}

/**
 * @brief Rotates the servo to the specified angle.
 *
 * This function commands the servo motor to move to a specific angle.
 * It uses the Servo library's `write` method to set the angle of the servo.
 *
 * @param angle The desired angle for the servo, in degrees. Valid range is typically 0 to 180.
 */
void turn(int angle) {



    servo.write(angle);

}


/**
 *
 */
void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(servo_pin, OUTPUT);
    servo.attach(9, 544, 2831);

    Serial.begin(9600);



}

/**
 * @brief Performs a continuous scanning operation over a range of angles using a servo motor,
 *        while measuring distance and sending the measured data.
 *
 * This function makes two passes over the servo's range of motion:
 * 1. A forward pass where the servo sweeps from 10 to 144 degrees in single-degree increments.
 * 2. A reverse pass where the servo sweeps back from 145 to 11 degrees in single-degree decrements.
 *
 * At each position, the servo pauses briefly, the distance to objects in front of the sensor is measured,
 * and the result is sent as data which includes the current servo angle and the measured distance.
 *
 * The delay between each step allows the servo motor to stabilize before taking measurements.
 *
 * @note This function is intended to run in a continuous loop to perform repeated scans.
 */
void loop() {

    for (int angle = 10; angle < 145; angle++){
        turn(angle);

        delay(30);
        float distance = measure_distance();
        sendData(angle, distance);
    }

    for (int angle = 145; angle > 10; angle--){
        turn(angle);

        delay(30);
        float distance = measure_distance();
        sendData(angle, distance);
    }

}



