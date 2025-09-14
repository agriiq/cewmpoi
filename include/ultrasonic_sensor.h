#pragma once
#include <Arduino.h>
class UltrasonicSensor {
public:
    void init();
    bool detectPerson();
};