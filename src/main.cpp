/**
 *@file RadarScanner
 *@author Daniel Pelzel
 *@brief measure Distance with HC-SR04 and Servo SG90 control
 */


#include <Arduino.h>
#include <Servo.h>

const uint8_t trig = 8; ///< Trigger pin for ultrasonic sensor (output)
const uint8_t echo = 7; ///< echo pin for ultrasonic sensor (input)
const uint8_t PWM = 9; ///< PWN-Signal for SG90 Servo


/**
 * Measures the distance to an object using an ultrasonic sensor.
 *
 * This function sends a trigger pulse through the trig pin of the ultrasonic sensor,
 * receives the echo signal through the echo pin, and calculates the distance based on
 * the time it takes for the signal to return. The calculation assumes that sound travels
 * at a speed of 340 m/s in air.
 *
 * @return The measured distance in centimeters.
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

void turn() {

}



void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(servo, OUTPUT);

    Serial.begin(9600);
}

void loop() {

    float distance_cm = measure_distance();
    Serial.println(distance_cm);
    delay(1000);
}

