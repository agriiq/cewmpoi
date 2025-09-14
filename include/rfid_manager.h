#pragma once
#include <Arduino.h>
class RFIDManager {
public:
    void init();
    bool scan1(String &uid); // Bereich 1
    bool scan2(String &uid); // Bereich 2
};