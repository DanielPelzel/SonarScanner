//
// Created by Daniel Pelzel on 23.03.26.
//
#include <Arduino.h>

const int trig = 8;
const int echo = 7;


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



void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
}

void loop() {

    float distance_cm = measure_distance();
    Serial.println(distance_cm);
    delay(1000);
}

