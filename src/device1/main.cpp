
#include "global.h"

AsyncWebServer serverEsp1(80);

void setup() {
  Serial.begin(115200);
  esp1PinSetup();
  eepromSetup();
  apEspSetup(esp2Mac, WIFI_AP_STA);
  serverSetup(serverEsp1);
  startUpMillis = millis();
}

void loop() {
  ArduinoOTA.handle();
  unsigned long currentMillis = millis();
  //// Water level////
  if (currentMillis - prevWaterMillis >= waterInterval){
    prevWaterMillis = currentMillis;
    readWaterLevel(OUT_PINS, outSum, water1Count, outLevel, outMeasured, gateMode, debugOut, true);
  }

  if (inMeasured && outMeasured){
    backgroundCheck();
    printInfo();

    inMeasured = outMeasured = 0;
  }
  /////////////////

  //Button logic////
  if (currentMillis - prevButtonMillis >= buttonInterval) {
    prevButtonMillis = currentMillis;
    buttonLogic();
  }
  ////////////////

  //// Gate logic ////
  if (currentMillis - prevGateMillis >= gateInterval) {
    prevGateMillis = currentMillis;
    gateLogic();

    //Print gate info
    if (gateCount == 5){
      printGateInfo();
      gateCount = 0;
    }
  }
  /////////////////

  //Force closing////
  if (closingPhase){
    if ((currentMillis - prevBotMillis) >= botInterval) {
      forceStop();
    }
  }

  //Startup//
  if (startUp){
    if ((currentMillis - startUpMillis) >= startUpInterval) {
      forceStop();
    }
  }

  if (motorStatus == "STANDBY"){
    if ((currentMillis - motorStandbyMillis) >= standByInterval) 
      deactivateMotor();
  }
  else if (motorStatus == "TRIGGERED"){
    if ((currentMillis - motorTrigMillis) >= motorTrigInterval) 
      triggerMotor();
  }

  if ((currentMillis - sendMobileMillis) >= sendMobileInterval){
    sendMobileMillis = currentMillis;
    sendToAndroid();
  }
}