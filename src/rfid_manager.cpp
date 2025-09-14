#include "rfid_manager.h"
#include <MFRC522.h>
#include "config.h"
#include <SPI.h>

MFRC522 rfid1(PIN_RC522_1_SS, PIN_RC522_1_RST);
MFRC522 rfid2(PIN_RC522_2_SS, PIN_RC522_2_RST);

void RFIDManager::init() {
    SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI);
    rfid1.PCD_Init();
    rfid2.PCD_Init();
}

bool scanRFID(MFRC522 &rfid, String &uid) {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return false;
    uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    rfid.PICC_HaltA();
    return true;
}

bool RFIDManager::scan1(String &uid) { return scanRFID(rfid1, uid); }
bool RFIDManager::scan2(String &uid) { return scanRFID(rfid2, uid); }