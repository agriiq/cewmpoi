#pragma once

#define PIN_LCD_SDA      21
#define PIN_LCD_SCL      22
#define PIN_OLED_SDA     21
#define PIN_OLED_SCL     22
#define PIN_RC522_1_SS   5
#define PIN_RC522_1_RST  17
#define PIN_RC522_2_SS   4
#define PIN_RC522_2_RST  16
#define PIN_SPI_SCK      18
#define PIN_SPI_MOSI     23
#define PIN_SPI_MISO     19
#define PIN_HCSR04_TRIG  26
#define PIN_HCSR04_ECHO  27
#define PIN_PIEZO        25
#define PIN_RELAY1       32
#define PIN_RELAY2       33

#define ADDR_LCD         0x27
#define ADDR_OLED        0x3C

#define DIST_THRESHOLD   10

// Richtiges Format: AES-Schlüssel als 16-Byte Hex-Array!
#define AES_KEY 0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x61,0x62,0x63,0x64,0x65,0x66
// Das entspricht ASCII "1234567890abcdef", KEIN String, KEIN {} drumherum!

#define UID_ENTRY_SIZE   24

#define DEBUG_SERIAL     Serial
#define SERIAL_BAUD      115200