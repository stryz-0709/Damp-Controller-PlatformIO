/*
 * print.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Aug 26, 2024
 *  Version 1: Init
 *  Author: Minh Tri
 */

//PRINT FOR DEBUGGING//

#include "print.h"

///Debug///
void printInfo() {
  Serial.print("IN: ");
  Serial.print(inLevel);
  Serial.print(", OUT: ");
  Serial.print(outLevel);
  Serial.print(", TOP: ");
  Serial.print(top_val);
  Serial.print(", BOTTOM: ");
  Serial.print(bot_val);
  Serial.print(", h1: ");
  Serial.print(h1);
  Serial.print(", h2: ");
  Serial.print(h2);
  Serial.print(", debugIn: ");
  Serial.print(debugIn);
  Serial.print(", debugOut: ");
  Serial.println(debugOut);
}

void printGateInfo(){
  Serial.print("Motor status: ");
  Serial.print(motorStatus);
  Serial.print(", ");
  Serial.print("closingPhase: ");
  Serial.print(closingPhase);
  Serial.print(", ");
  Serial.print(gateStatus);
  Serial.print(", ");
  Serial.println(gateMode);
}

void printInputs(){
  Serial.print(endButton);
  Serial.print(getWater);
  Serial.print(removeWater);
  Serial.print(top_val);
  Serial.println(bot_val);
}