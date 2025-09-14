#include "ultrasonic_sensor.h"
#include "config.h"
void UltrasonicSensor::init() {
    pinMode(PIN_HCSR04_TRIG, OUTPUT);
    pinMode(PIN_HCSR04_ECHO, INPUT);
}
bool UltrasonicSensor::detectPerson() {
    digitalWrite(PIN_HCSR04_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_HCSR04_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_HCSR04_TRIG, LOW);
    long duration = pulseIn(PIN_HCSR04_ECHO, HIGH, 30000);
    float cm = duration / 58.0;
    return (cm > 0 && cm < DIST_THRESHOLD);
}