#include "lcd_display.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "config.h"
LiquidCrystal_I2C lcd(ADDR_LCD, 16, 2);
void LCDDisplay::init() { lcd.init(); lcd.backlight(); }
void LCDDisplay::showMessage(const String &text) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text);
}