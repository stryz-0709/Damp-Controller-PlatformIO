/*
 * control.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 3: Remove Automatic gate control
 *  Version 3.1: Change sendLedInfo parameter from 4 to 0
 *  Author: Minh Tri
 */

///GATE CONTROL - OPEN, CLOSE & FORCE_CLOSE///

#include "control.h"

////Controlling gate////

void closingGate(){
  if (isBot){
    gateStatus = "STOPPED";
    return;
  }
  // Serial.println("CLOSING GATE");
  digitalWrite(VALVE_UP, HIGH);
  if (bot_val) {
    if (!closingPhase) prevBotMillis = millis();
    closingPhase = true;
  } 
  else if (!closingPhase) {
    if (motorStatus == "OFF") activateMotor();
    else if (motorStatus == "DELAY" && millis() - motorDelayMillis >= motorOnInterval) {
      Serial.println("RELAY ACTIVATED");
      digitalWrite(VALVE_DOWN, LOW);
      motorStatus = "ACTIVE";
    }
    else if (motorStatus == "ACTIVE") digitalWrite(VALVE_DOWN, LOW);
  }
}

void openingGate(String mode) {
  digitalWrite(VALVE_DOWN, HIGH);
  ///If gate touches top switch///
  if (top_val) {
    digitalWrite(VALVE_UP, HIGH);
    if (motorStatus == "ACTIVE") activateStandby();
  }

  ///Force close in MANUAL mode///
  if ((gateStatus == "GET_WATER" && inLevel >= outLevel) || (gateStatus == "REMOVE_WATER" && inLevel <= outLevel)){
    gateStatus = "FORCE_CLOSE";
    closingGate();
    return;
  }

  ///If motor is not active///
  if (motorStatus == "OFF" && !top_val) activateMotor();
  else if (motorStatus == "DELAY" && (millis() - motorDelayMillis >= motorOnInterval)) {
    Serial.println("RELAY ACTIVATED");
    digitalWrite(VALVE_UP, LOW);
    motorStatus = "ACTIVE";
    isBot = 0;
  }
  else if (motorStatus == "ACTIVE") digitalWrite(VALVE_UP, LOW);
}

void forceClose(){
  Serial.println("VALVE_DOWN STOPPED");
  gateStatus = "STOPPED";
  digitalWrite(VALVE_DOWN, HIGH);
  closingPhase = false;
  activateStandby();
  sendLedInfo(0); //TURN OFF START_RELAY
  isBot = 1;
}