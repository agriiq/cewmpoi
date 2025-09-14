#include "relay_control.h"
#include "config.h"
static String b2_uid = "";
static unsigned long b2_temp_close_until = 0;
void RelayControl::init() {
    pinMode(PIN_RELAY1, OUTPUT); digitalWrite(PIN_RELAY1, LOW);
    pinMode(PIN_RELAY2, OUTPUT); digitalWrite(PIN_RELAY2, LOW);
}
void RelayControl::open1() { digitalWrite(PIN_RELAY1, HIGH); }
void RelayControl::close1() { digitalWrite(PIN_RELAY1, LOW); }
void RelayControl::open2(const String &uid) { b2_uid = uid; digitalWrite(PIN_RELAY2, HIGH); }
void RelayControl::close2() { b2_uid = ""; digitalWrite(PIN_RELAY2, LOW); }
void RelayControl::close2Temp() { close2(); b2_temp_close_until = millis() + 15000; }
bool RelayControl::isB2Free() const { return b2_uid == "" && millis() > b2_temp_close_until; }
bool RelayControl::isB2Open(const String &uid) const { return b2_uid == uid; }
bool RelayControl::isB2OpenFor(const String &uid) const { return b2_uid == uid; }