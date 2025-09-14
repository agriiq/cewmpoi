#include "crypto_storage.h"
#include "config.h"
#include <LittleFS.h>
#include <mbedtls/aes.h>

const char* uid_file = "/uids.dat";
const uint8_t aes_key[16] = { AES_KEY }; // siehe config.h

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
        File f = LittleFS.open(uid_file, "w");
        if (f) {
            f.close();
        }
    }
}

int CryptoStorage::checkUID(const String &uid) {
    File f = LittleFS.open(uid_file, "r");
    if (!f) {
        return 0;
    }

    uint8_t encrypted[UID_ENTRY_SIZE];
    uint8_t plain[UID_ENTRY_SIZE + 1];

    while (f.read(encrypted, UID_ENTRY_SIZE) == UID_ENTRY_SIZE) {
        aes_decrypt(encrypted, plain);
        plain[UID_ENTRY_SIZE] = '\0';
        String entry(reinterpret_cast<char*>(plain));
        int sep = entry.indexOf(':');
        if (sep > 0) {
            String storedUid = entry.substring(0, sep);
            int perm = entry.substring(sep + 1).toInt();
            if (storedUid == uid) {
                f.close();
                return perm;
            }
        }
    }

    f.close();
    return 0;
}