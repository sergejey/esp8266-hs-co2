#include <Arduino.h>
#include <SoftwareSerial.h>
#include <config.h>
#include <oled.h>
#include <mqtt_com.h>

#include <MHZ19.h>  //https://github.com/strange-v/MHZ19

//for conecting with MH-Z19
SoftwareSerial ss;
MHZ19 mhz(&ss);

unsigned int last_measured_time = 0; //last measure timestamp

void startCO2() {
  //ss.begin(9600);
  ss.begin(9600,SWSERIAL_8N1,CO2_RX_PIN,CO2_TX_PIN);
  displayPrint("MH-Z19 initializing... ");
  //mhz.setAutoCalibration(false);
}

void handleCO2() {
 unsigned int tm = round(millis() / 1000);
 if ((tm-last_measured_time)>10) {
     last_measured_time=tm;
     displayPrint("Reading MH-Z19 data...");
     MHZ19_RESULT response = mhz.retrieveData();
     if (response == MHZ19_RESULT_OK)
     {
        String payload;
        payload = "{'co2':'";
        payload += mhz.getCO2();
        payload += "', 'temperature':";
        payload += mhz.getTemperature();
        payload += "', 'accuracy':";
        payload += mhz.getAccuracy();
        payload += "', 'minco2':";
        payload += mhz.getMinCO2();    
        payload += "}";
        publishEvent("io",payload);
        displayPrint(payload);
     } else {
         String reason = "Unknown";
         if (response == MHZ19_RESULT_ERR_FB) {
            reason = "FB error";
         } else if (response == MHZ19_RESULT_ERR_SB) {
            reason = "SB error";
         } else if (response == MHZ19_RESULT_ERR_CRC) {
            reason = "CRC error";
         } else if (response == MHZ19_RESULT_ERR_TIMEOUT) {
            reason = "Timeout";
         }
         displayPrint("Cannot read MH-Z19: "+reason+'.');
     }
     
 }

}