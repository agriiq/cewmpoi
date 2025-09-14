#include "crypto_storage.h"
#include "config.h"
#include <LittleFS.h>
#include <mbedtls/aes.h>

const char* uid_file = "/uids.dat";
const uint8_t aes_key[16] = AES_KEY; // siehe config.h

void aes_encrypt(const uint8_t* plain, uint8_t* encrypted) {
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, aes_key, 128);
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, plain, encrypted);
    mbedtls_aes_free(&ctx);
}

void aes_decrypt(const uint8_t* encrypted, uint8_t* plain) {
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_dec(&ctx, aes_key, 128);
    mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_DECRYPT, encrypted, plain);
    mbedtls_aes_free(&ctx);
}

void CryptoStorage::init() {
    if (!LittleFS.exists(uid_file)) {
        // Erstelle Demo-Daten: UID + Berechtigung (1 oder 2)
        File f = LittleFS.open(uid_file, "w");
        if (f) {
            // Beispiel-UIDs (normalerweise würden diese verschlüsselt gespeichert)
            f.println("04e3f722:2");  // Karte mit Berechtigung für beide Bereiche
            f.println("12345678:1");  // Karte nur für Bereich 1
            f.close();
            DEBUG_SERIAL.println("[CRYPTO] Demo-UID-Datei erstellt");
        }
    }
}

int CryptoStorage::checkUID(const String &uid) {
    File f = LittleFS.open(uid_file, "r");
    if (!f) {
        DEBUG_SERIAL.println("[CRYPTO] Fehler: UID-Datei nicht lesbar");
        return 0;
    }
    
    String line;
    while (f.available()) {
        line = f.readStringUntil('\n');
        line.trim();
        
        int colonPos = line.indexOf(':');
        if (colonPos > 0) {
            String stored_uid = line.substring(0, colonPos);
            int permission = line.substring(colonPos + 1).toInt();
            
            if (stored_uid.equalsIgnoreCase(uid)) {
                f.close();
                DEBUG_SERIAL.println("[CRYPTO] UID gefunden: " + uid + " (Berechtigung: " + permission + ")");
                return permission;
            }
        }
    }
    
    f.close();
    DEBUG_SERIAL.println("[CRYPTO] UID unbekannt: " + uid);
    return 0; // UID nicht gefunden
}