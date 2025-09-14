#pragma once
#include <Arduino.h>
class CryptoStorage {
public:
    void init();
    int checkUID(const String &uid); // 0=unbekannt, 1=Bereich1, 2=Bereich1+2
};