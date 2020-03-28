#include <Arduino.h>
#include <config.h>

#ifdef CONFIG_DISPLAY_SPI
#include <SPI.h>
#include "SH1106Spi.h"   // https://github.com/ThingPulse/esp8266-oled-ssd1306
SH1106Spi display(OLED_RESET, OLED_DC, OLED_CS); // FOR SPI
#endif

#ifdef CONFIG_DISPLAY_I2C
#include <Wire.h>
#include "SH1106Wire.h"   // https://github.com/ThingPulse/esp8266-oled-ssd1306
SH1106Wire   display(OLED_ADDR, OLED_SDA, OLED_SDC);    // For I2C
#endif

void displayPrint(String s) {
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128, s);
    display.display();
}

void startOLED() {
    display.init();
    display.resetDisplay();
    display.flipScreenVertically();
    displayPrint("Initializing...");
}

