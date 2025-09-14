# ESP32 Zutrittskontrollsystem

## Hardware
- ESP32 DevKit
- 2× RC522 (SPI)
- LCD 16x2 I²C (Bereich 1)
- OLED SSD1306 I²C (Bereich 2)
- HC-SR04 Ultraschall
- 2× Relais (Platzhalter)
- Piezo (KY-006, GPIO25)

## Features
- Bereich 1: RFID-Schutz, LCD-Anzeige, Relais1
- Bereich 2: Ultraschall-Trigger, OLED-Status, Relais2, erweiterte Logik
- UID-Liste verschlüsselt (AES, SPIFFS)
- Serielle Debug-Ausgabe (115200 Baud)
- Modular, robust, dokumentiert

## ToDo
- Verschlüsselte UID-Liste implementieren
- Admininterface (seriell) ausbauen
- Relaissteuerung/LEDs finalisieren

## Hinweise
Jede Moduldatei ist kommentiert und kann erweitert werden!