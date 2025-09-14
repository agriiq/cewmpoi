#include "buzzer.h"
#include "config.h"

void BuzzerControl::init() {
    pinMode(PIN_PIEZO, OUTPUT);
}

void BuzzerControl::beepSuccess() {
    tone(PIN_PIEZO, 1000, 100); delay(120);
    tone(PIN_PIEZO, 1500, 80);  delay(90);
    noTone(PIN_PIEZO);
}

void BuzzerControl::beepError() {
    tone(PIN_PIEZO, 600, 250); delay(300);
    noTone(PIN_PIEZO);
}