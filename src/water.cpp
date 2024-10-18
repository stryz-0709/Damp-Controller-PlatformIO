/*
 * water.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 9, 2024
 *  Version 3: Merge function of ESP1 & ESP2
 *  Author: Minh Tri
 */

//READ WATER LEVEL//

#include "water.h"

//Read water level
void readWaterLevel() {
  int inBinary = 0;
  int outBinary = 0;
  int inRes = 0;
  int outRes = 0;
  int base = 1;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(IN_PINS[i])) inRes = i + 1;
    if (digitalRead(OUT_PINS[i])) inRes = i + 1;
    inBinary += digitalRead(IN_PINS[i]) * base;
    outBinary += digitalRead(OUT_PINS[i]) * base;
    base *= 10;
  }

  Serial.print("In: ");
  Serial.print(inBinary);
  Serial.print(" -> ");
  Serial.print(inRes);
  Serial.print(" , Out: ");
  Serial.print(outBinary);
  Serial.print(" -> ");
  Serial.println(outRes);
  
  inSum += inRes;
  outSum += outRes;
  waterCount++;

  if (waterCount == countInterval) {
    inLevel = round(inSum / (float)countInterval);
    outLevel = round(outSum / (float)countInterval);
    
    inLevel = (gateMode == "DEBUG") ? debugIn : inLevel; 
    outLevel = (gateMode == "DEBUG") ? debugOut : outLevel; 
    inMeasured = 1;
    outMeasured = 1;

    waterCount = 0;
    inSum = 0;
    outSum = 0;
  }
}
