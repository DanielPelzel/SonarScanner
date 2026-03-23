//
// Created by Daniel Pelzel on 23.03.26.
//
#include <Arduino.h>


//Variablen definieren
float seconds;
float distance_m;
float distance_cm;


void setup() {
    pinMode(13, OUTPUT);
    pinMode(12, INPUT);
    Serial.begin(9600);
}

void loop() {

    // Sicherstellen, dass der Pin vorher LOW ist
    digitalWrite(13, LOW);
    delayMicroseconds(2);

    //Sending Input signal (10 microseconds)

    digitalWrite(13, HIGH);
    delayMicroseconds(10);
    digitalWrite(13, LOW);

    //ultrasonic wave time

    seconds = pulseIn(12, HIGH) * 1e-6;


    //time to distance calc.

    distance_m = (seconds * 340.0 /2.0);
    distance_cm = distance_m * 100;
    Serial.println(distance_cm);



}