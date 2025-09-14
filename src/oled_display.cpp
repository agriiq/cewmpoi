#include "oled_display.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "config.h"
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
void OLEDDisplay::init() { oled.begin(SSD1306_SWITCHCAPVCC, ADDR_OLED); oled.clearDisplay(); }
void OLEDDisplay::showMessage(const String &line1, const String &line2) {
    oled.clearDisplay();
    oled.setTextSize(1); oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0); oled.println(line1);
    oled.setCursor(0, 16); oled.println(line2);
    oled.display();
}