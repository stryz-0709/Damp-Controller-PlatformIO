#include "water.h"

//Read water level
void readWaterLevel(const int* pins, int& sum, int& count, int& level, int& measured, const String& mode, int debugValue, bool isOut) {
  int binary = 0;
  int res = 0;
  int base = 1;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(pins[i])) res = i + 1;
    binary += digitalRead(pins[i]) * base;
    base *= 10;
  }

  Serial.print(binary);
  Serial.print(" -> ");
  Serial.println(res);
  
  sum += res;
  count++;

  if (count == countInterval) {
    level = round(sum / (float)countInterval);
    
    if (isOut) { 
      level = (mode == "DEBUG") ? debugValue : level;  // For out water level
      measured = 1;
    } 
    else sendWaterInfo(level);  // For in water level

    count = 0;
    sum = 0;
  }
}
