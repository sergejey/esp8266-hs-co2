#ifndef config_h
#define config_h

const int CO2_TX_PIN = D4; //tx 
const int CO2_RX_PIN = D1; //rx

#define CONFIG_DISPLAY_SPI
//#define CONFIG_DISPLAY_I2C

#ifdef CONFIG_DISPLAY_SPI
const int OLED_CS     = D8; //GPIO15 - Chip select (CS)
const int OLED_DC     = D2; //GPIO4  - Data/Command (DC)
const int OLED_RESET  = 10; //GPIO10 SDD3 - RESET (RST)
#endif

#ifdef CONFIG_DISPLAY_I2C
#define OLED_ADDR   0x3C
const int OLED_SDA    = D7; //GPIO13 - SDA  (D1)
const int OLED_SDC    = D5; //GPIO14 - CLK (D0)
#endif

const int EEPROM_MQTT_DEVICE_TITLE = 50;
const int EEPROM_MQTT_USER = 100;
const int EEPROM_MQTT_PASSWORD = 150;
const int EEPROM_MQTT_SERVER = 200;
const int EEPROM_MQTT_BASE = 250;


#endif