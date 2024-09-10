/*
 * logic.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Aug 26, 2024
 *  Version 1: Init
 *  Author: Minh Tri
 */

//LOGIC FOR BUTTONS AND GATE//


#include "logic.h"

void buttonLogic(){
  readInputs();

  //START//
  if (endButton && endButton != prevEndButton){
    Serial.println("FORCE_CLOSE");
    gateMode = "END";
    gateStatus = "FORCE_CLOSE";
    sendLedInfo(0);
  }

  //GET WATER//
  if (getWater && getWater != prevGetWater && gateMode != "END"){
    if (outToIn && gateStatus != "FORCE_CLOSE") gateStatus = "GET_WATER";
    else if (!outToIn) Serial.println("Condition outToIn by hand not met.");
  }

  //REMOVE WATER//
  if (removeWater && removeWater != prevRemoveWater && gateMode != "END"){
    if (inToOut && gateStatus != "FORCE_CLOSE") gateStatus = "REMOVE_WATER";
    else if (!inToOut) Serial.println("Condition inToOut by hand not met.");
  }
}

void gateLogic(){
  gateCount++;
  // Opening and closing logic
  if (gateStatus == "FORCE_CLOSE") closingGate();
  else if (gateStatus == "GET_WATER" || gateStatus == "REMOVE_WATER") openingGate(gateStatus);
  else if (gateStatus == "STOPPED"){
    if (motorStatus == "ACTIVE") activateStandby();
    else{
      digitalWrite(MOTOR_TRIG, HIGH);
      digitalWrite(MOTOR, HIGH);
    } 
    digitalWrite(VALVE_UP, HIGH);
    digitalWrite(VALVE_DOWN, HIGH);
  }
}