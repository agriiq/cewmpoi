#pragma once
#include <Arduino.h>
class LCDDisplay {
public:
    void init();
    void showMessage(const String &text);
};