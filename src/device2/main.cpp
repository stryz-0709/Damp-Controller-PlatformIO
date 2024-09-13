
#include "global.h"

AsyncWebServer serverEsp2(80);

void setup() {
  Serial.begin(115200);
  esp2PinSetup();
  apEspSetup(esp1Mac, WIFI_STA);
  WebSerial.begin(&serverEsp2);
  serverEsp2.begin();
}

void loop() {
  ArduinoOTA.handle();
  unsigned long currentMillis = millis();
  //// Water level////
  if (currentMillis - prevWater2Millis >= waterInterval){
    prevWater2Millis = currentMillis;
    readWaterLevel(IN_PINS, inSum, water2Count, inLevel, outMeasured, gateMode, debugOut, false);
  }
}