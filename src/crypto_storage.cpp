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

// ... Rest wie bereits geliefert (init und checkUID)