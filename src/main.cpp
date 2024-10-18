
#include "global.h"

AsyncWebServer serverEsp1(80);

void setup() {
  Serial.begin(115200);
  pinSetup();
  eepromSetup();
  apEspSetup();
  serverSetup(serverEsp1);
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  startUpMillis = millis();
}

void loop() {
  ArduinoOTA.handle();
  unsigned long currentMillis = millis();

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

  //// Water level////
  if (currentMillis - prevWaterMillis >= waterInterval){
    prevWaterMillis = currentMillis;
    readWaterLevel();
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

  if (builtInButton) resetEEPROM();

  if (turnOff){
    digitalWrite(START_BUTTON, HIGH);     
    digitalWrite(TOWER_LED, HIGH);   
  }

  

  
}