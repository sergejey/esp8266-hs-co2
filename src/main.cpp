#include <Arduino.h>

#include <config.h>
#include <utils.h>
#include <wifi_com.h>
#include <web_com.h>
#include <mqtt_com.h>
#include <ota.h>
#include <oled.h>
#include <co2.h>

long latestTempRequested = 0;

long lastMsg = 0;
char msg[50];

int lastPingSent = 0;

void setup() {

  startEEPROM();
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);

  delay(10);

  startOLED();
  startWiFi();
  startMQTT();
  startWeb();
  startCO2();

  String device_id = WiFi.macAddress();
  device_id.replace(":", "");
  String access_point_name = "MHS"+device_id;
  startOTA(access_point_name);


}


void loop() {

  int tm = round(millis() / 1000);

  handleOTA();
  handleWeb();
  handleMQTT();

  handleCO2();

  if ((tm - lastPingSent) > 60) {
    String payload;
    payload = "{'ip':'";
    payload += WiFi.localIP().toString();
    payload += "', 'uptime':";
    payload += tm;
    payload += "','signal':";
    payload += getWiFiQuality();
    payload += "}";
    publishEvent("ping",payload);
    displayPrint(payload);
    lastPingSent = tm;
  }

}
