#include <Arduino.h>
#include "config.h"
#include "rfid_manager.h"
#include "crypto_storage.h"
#include "lcd_display.h"
#include "oled_display.h"
#include "ultrasonic_sensor.h"
#include "relay_control.h"
#include "buzzer.h"
#include <LittleFS.h>

// Globale Instanzen:
RFIDManager rfid;
CryptoStorage crypto;
LCDDisplay lcd;
OLEDDisplay oled;
UltrasonicSensor usensor;
RelayControl relay;
BuzzerControl buzzer;

void setup() {
    DEBUG_SERIAL.begin(SERIAL_BAUD);
    LittleFS.begin();
    lcd.init();
    oled.init();
    buzzer.init();
    relay.init();
    crypto.init();
    rfid.init();
    usensor.init();

    lcd.showMessage("System startet...");
    oled.showMessage("Boot...", "Bitte warten");
    buzzer.beepError();  // kurzer Selbsttest-Ton
    delay(1000);
}

void loop() {
    // Bereich 1: RFID alle 3s, LCD anzeigen, Relais1 ggf. schalten
    static unsigned long lastScan1 = 0;
    if (millis() - lastScan1 > 3000) {
        lastScan1 = millis();
        String uid;
        if (rfid.scan1(uid)) {
            int perm = crypto.checkUID(uid);
            if (perm >= 1) {
                lcd.showMessage("WILLKOMMEN");
                relay.open1();
                buzzer.beepSuccess();
                DEBUG_SERIAL.println("[B1] Zutritt gewaehrt: " + uid);
            } else {
                lcd.showMessage("ZUTRITT VERWEIGERT");
                relay.close1();
                buzzer.beepError();
                DEBUG_SERIAL.println("[B1] Zutritt verweigert: " + uid);
            }
        }
    }

    // Bereich 2: Ultraschall-Überwachung
    if (usensor.detectPerson()) {
        oled.showMessage("Annäherung erkannt", "Bitte Karte scannen!");
        String uid;
        if (rfid.scan2(uid)) {
            int perm = crypto.checkUID(uid);
            if (perm == 2) {
                if (relay.isB2Open(uid)) {
                    relay.close2();
                    oled.showMessage("Bereich 2", "geschlossen");
                    buzzer.beepSuccess();
                    DEBUG_SERIAL.println("[B2] Bereich geschlossen durch: " + uid);
                } else if (relay.isB2Free()) {
                    relay.open2(uid);
                    oled.showMessage("Zutritt Bereich 2", "erlaubt");
                    buzzer.beepSuccess();
                    DEBUG_SERIAL.println("[B2] Zutritt gewaehrt: " + uid);
                } else if (!relay.isB2OpenFor(uid)) {
                    relay.close2Temp();
                    oled.showMessage("Zutritt verweigert", "Bitte spaeter!");
                    buzzer.beepError();
                    DEBUG_SERIAL.println("[B2] Falscher Versuch: " + uid);
                }
            } else {
                oled.showMessage("Keine Berech.", "Karte nicht erlaubt");
                buzzer.beepError();
                DEBUG_SERIAL.println("[B2] Keine Berechtigung: " + uid);
            }
        }
    } else {
        oled.showMessage("Bereich 2", "Warten auf Person...");
    }

    delay(30);
}