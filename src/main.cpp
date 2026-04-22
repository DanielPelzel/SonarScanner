/**
 *@file SonarScanner
 *@author Daniel Pelzel
 *@brief measure Distance with HC-SR04 and Servo SG90 control
 */


#include <Arduino.h>
#include <Servo.h>

/**
 * @brief Represents a servo motor instance.
 */
Servo servo;

const uint8_t trig = 8; /**
 * @brief Pin number for the ultrasonic sensor's "Trig" signal.
 */
const uint8_t echo = 7; /**
 * @brief Pin connected to the servo motor signal line.
 */
const uint8_t servo_pin = 9; ///< PWN-Signal for SG90 Servo


/**
 * @brief Measures the distance to an object using an ultrasonic sensor.
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
 * @param angle The desired angle for the servo, in degrees.
 */
void turn(int angle) {
    servo.write(angle);
}


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



