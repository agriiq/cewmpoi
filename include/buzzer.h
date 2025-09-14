#pragma once
#include <Arduino.h>
class BuzzerControl {
public:
    void init();
    void beepSuccess();
    void beepError();
};