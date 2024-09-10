
#ifndef INC_WATER_H_
#define INC_WATER_H_

#include "global.h"

void readWaterLevel(const int* pins, int& sum, int& count, int& level, int& measured, const String& mode, int debugValue, bool isOut);


#endif /* INC_WATER_H_ */