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
  
  // WebSerial.print("IN: ");
  // WebSerial.print(inLevel);
  // WebSerial.print(", OUT: ");
  // WebSerial.print(outLevel);
  // WebSerial.print(", TOP: ");
  // WebSerial.print(top_val);
  // WebSerial.print(", BOTTOM: ");
  // WebSerial.print(bot_val);
  // WebSerial.print(", h1: ");
  // WebSerial.print(h1);
  // WebSerial.print(", h2: ");
  // WebSerial.print(h2);
  // WebSerial.print(", debugIn: ");
  // WebSerial.print(debugIn);
  // WebSerial.print(", debugOut: ");
  // WebSerial.println(debugOut);
}

void printGateInfo(){
  Serial.print("Motor status: ");
  Serial.print(motorStatus);
  Serial.print(", ");
  Serial.print("closingPhase: ");
  Serial.print(closingPhase);
  Serial.print(", ");
  Serial.print("startUp: ");
  Serial.print(startUp);
  Serial.print(", ");
  Serial.print("isBot: ");
  Serial.print(isBot);
  Serial.print(", ");
  Serial.print(gateStatus);
  Serial.print(", ");
  Serial.println(gateMode);

  // WebSerial.print("Motor status: ");
  // WebSerial.print(motorStatus);
  // WebSerial.print(", ");
  // WebSerial.print("closingPhase: ");
  // WebSerial.print(closingPhase);
  // WebSerial.print(", ");
  // WebSerial.print("startUp: ");
  // WebSerial.print(startUp);
  // WebSerial.print(", ");
  // WebSerial.print("isBot: ");
  // WebSerial.print(isBot);
  // WebSerial.print(", ");
  // WebSerial.print(gateStatus);
  // WebSerial.print(", ");
  // WebSerial.println(gateMode);
}

void printInputs(){
  Serial.print(endButton);
  Serial.print(getWater);
  Serial.print(removeWater);
  Serial.print(top_val);
  Serial.println(bot_val);

  // WebSerial.print(endButton);
  // WebSerial.print(getWater);
  // WebSerial.print(removeWater);
  // WebSerial.print(top_val);
  // WebSerial.println(bot_val);
}