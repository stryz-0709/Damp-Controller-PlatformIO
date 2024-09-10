
#include "global.h"

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  esp2PinSetup();
  apEspSetup("", 0, 0, 0, 0, esp1, WIFI_STA, false);
}

void loop() {
  unsigned long currentMillis = millis();
  //// Water level////
  if (currentMillis - prevWater2Millis >= waterInterval){
    prevWater2Millis = currentMillis;
    readWaterLevel(IN_PINS, inSum, water2Count, inLevel, outMeasured, gateMode, debugOut, false);
  }
}