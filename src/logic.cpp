/*
 * logic.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 1: Init
 *  Version 2: Add logic for toggling tower led
 *  Version 2.2: Revert toggling function
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
  if (gateStatus == "FORCE_CLOSE"){
    //TURN ON TOWER_LED WITHOUT GET_WATER_LED/REMOVE_WATER_LED
    sendLedInfo(3);
    closingGate();
  } 
  else if (gateStatus == "GET_WATER" || gateStatus == "REMOVE_WATER"){
    //1 TO TURN ON GET_WATER_LED, 2 TO TURN ON REMOVE_WATER_LED;
    sendLedInfo((gateStatus == "GET_WATER")? 1 : 2);
    openingGate(gateStatus);
  } 
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