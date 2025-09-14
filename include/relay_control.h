#pragma once
#include <Arduino.h>
class RelayControl {
public:
    void init();
    void open1();
    void close1();
    void open2(const String &uid);
    void close2();
    void close2Temp();
    bool isB2Free() const;
    bool isB2Open(const String &uid) const;
    bool isB2OpenFor(const String &uid) const;
};