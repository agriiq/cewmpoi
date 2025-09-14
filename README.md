# ESP32 Zutrittskontrollsystem

Ein modulares ESP32-basiertes Zutrittskontrollsystem mit verschlüsselter UID-Speicherung und dualer Bereichskontrolle.

## 🔧 Hardware

### Komponenten
- ESP32 DevKit v1
- 2× RC522 RFID-Module (SPI)
- LCD 16x2 mit I²C-Backpack (Bereich 1)
- OLED SSD1306 128x64 I²C (Bereich 2) 
- HC-SR04 Ultraschallsensor
- 2× Relais-Module (5V)
- Piezo-Summer (KY-006)

### Pinbelegung
```
I²C Bus:
- SDA: GPIO21 (LCD & OLED)
- SCL: GPIO22 (LCD & OLED)

SPI Bus (RFID):
- SCK:  GPIO18
- MISO: GPIO19  
- MOSI: GPIO23
- SS1:  GPIO5  (RC522 #1)
- SS2:  GPIO4  (RC522 #2)
- RST1: GPIO17 (RC522 #1)
- RST2: GPIO16 (RC522 #2)

Digital I/O:
- TRIG:   GPIO26 (HC-SR04)
- ECHO:   GPIO27 (HC-SR04)
- PIEZO:  GPIO25
- RELAY1: GPIO32 (Bereich 1)
- RELAY2: GPIO33 (Bereich 2)

I²C-Adressen:
- LCD:  0x27
- OLED: 0x3C
```

## 🚀 Features

### Bereich 1 (Basis-Zutrittskontrolle)
- RFID-Scanner alle 3 Sekunden
- LCD-Statusanzeige
- Relais-Steuerung für Türöffner
- Sofortige Zutrittskontrolle

### Bereich 2 (Erweiterte Logik)
- Ultraschall-basierte Annäherungserkennung
- OLED-Display für detaillierte Anzeigen
- Intelligente Zutrittskontrolle:
  - Toggle-Funktion (öffnen/schließen)
  - Besetzt-Erkennung
  - Temporäre Sperrung bei falschen Versuchen

### Sicherheit & Speicherung
- UID-Liste verschlüsselt in LittleFS
- AES-128 Verschlüsselung für sensible Daten
- Berechtigung-Levels: 1 (nur Bereich 1), 2 (beide Bereiche)
- Serielle Debug-Ausgabe (115200 Baud)

## 🛠️ Installation & Build

### Voraussetzungen
```bash
# Python 3.x installieren
# PlatformIO Core installieren
pip install platformio
```

### Build-Prozess

#### Option 1: PlatformIO (Empfohlen)
```bash
# Dependencies installieren
pio platform install espressif32
pio lib install

# Projekt kompilieren
pio run

# Auf ESP32 flashen
pio run --target upload

# Serial Monitor
pio device monitor --baud 115200
```

#### Option 2: Makefile (Alternative)
```bash
# Alle Kommandos anzeigen
make help

# Projekt bauen
make build

# Auf ESP32 flashen und Monitor starten
make flash

# Nur kompilieren (ohne Upload)
make verify
```

### Erste Inbetriebnahme
1. ESP32 mit USB verbinden
2. Code flashen: `pio run --target upload`
3. Serial Monitor öffnen: `pio device monitor`
4. System startet automatisch und erstellt Demo-UIDs

## 📁 Projektstruktur

```
cewmpoi/
├── platformio.ini          # PlatformIO Konfiguration
├── Makefile                # Alternative Build-System
├── README.md               # Diese Dokumentation
├── include/                # Header-Dateien
│   ├── config.h           # Hardware-Konfiguration & Pins
│   ├── rfid_manager.h     # RFID-Scanner Interface
│   ├── crypto_storage.h   # Verschlüsselte UID-Verwaltung
│   ├── lcd_display.h      # LCD-Anzeige (16x2)
│   ├── oled_display.h     # OLED-Anzeige (128x64)
│   ├── ultrasonic_sensor.h # HC-SR04 Sensor
│   ├── relay_control.h    # Relais-Steuerung
│   └── buzzer.h           # Piezo-Summer
└── src/                   # Implementierung
    ├── main.cpp           # Hauptprogramm & Setup
    ├── rfid_manager.cpp   # RFID-Scanner Logik
    ├── crypto_storage.cpp # AES-Verschlüsselung & UID-DB
    ├── lcd_display.cpp    # LCD-Steuerung
    ├── oled_display.cpp   # OLED-Steuerung  
    ├── ultrasonic_sensor.cpp # Ultraschall-Logik
    ├── relay_control.cpp  # Relais-Verwaltung
    └── buzzer.cpp         # Signaltöne
```

## 🔑 Verwendung

### Demo-UIDs (Standard)
Nach dem ersten Start werden automatisch Demo-UIDs erstellt:
- `04e3f722`: Berechtigung Level 2 (beide Bereiche)
- `12345678`: Berechtigung Level 1 (nur Bereich 1)

### Betrieb

#### Bereich 1 (LCD)
1. RFID-Karte vor Scanner 1 halten
2. Bei gültiger Karte: "WILLKOMMEN" + Relais aktiviert
3. Bei ungültiger Karte: "ZUTRITT VERWEIGERT" + Fehlerton

#### Bereich 2 (OLED)
1. Person nähert sich (Ultraschall < 10cm)
2. "Bitte Karte scannen" erscheint
3. RFID-Karte vor Scanner 2 halten
4. Bei Berechtigung Level 2:
   - Bereich frei → Zugang gewährt
   - Bereich von gleicher Karte geöffnet → Bereich schließen
   - Bereich von anderer Karte besetzt → Zugang verweigert

## 🛡️ Sicherheit

- **AES-128 Verschlüsselung**: Alle UID-Daten verschlüsselt gespeichert
- **Schlüssel-Management**: AES-Key in `config.h` definiert
- **Berechtigung-Levels**: Granulare Zugriffskontrolle
- **Audit-Trail**: Vollständige Logging über Serial

## 🔧 Konfiguration

Alle Hardware-Einstellungen in `include/config.h`:
- Pin-Definitionen  
- I²C-Adressen
- Sicherheits-Parameter
- AES-Schlüssel

## 📊 Debugging

Serial Monitor (115200 Baud) zeigt:
- Systemstart-Informationen
- RFID-Scan-Ergebnisse  
- Zugriffs-Entscheidungen
- Fehler und Warnungen

## 🚧 Entwicklung

### Code-Stil
- Modularer Aufbau mit klarer Trennung
- Aussagekräftige Klassen- und Methodennamen
- Umfassende Dokumentation
- Einheitliche Fehlerbehandlung

### Erweiterungen
- UID-Verwaltung über Web-Interface
- Zeitbasierte Zugangsregeln
- Externe Datenbank-Anbindung
- MQTT/WiFi-Integration

## 📝 TODO

- [x] Verschlüsselte UID-Liste implementiert (Demo-Version)
- [ ] Web-basiertes Admin-Interface
- [ ] WiFi-Konfiguration über Portal
- [ ] Zeitgesteuerte Zugangsregeln
- [ ] Backup/Restore-Funktionen
- [ ] OTA-Updates

## 🤝 Beitragen

1. Repository forken
2. Feature-Branch erstellen
3. Änderungen committen
4. Pull Request erstellen

## 📄 Lizenz

Dieses Projekt ist Open Source. Weitere Details in der LICENSE-Datei.