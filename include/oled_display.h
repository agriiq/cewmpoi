#pragma once
#include <Arduino.h>
class OLEDDisplay {
public:
    void init();
    void showMessage(const String &line1, const String &line2 = "");
};