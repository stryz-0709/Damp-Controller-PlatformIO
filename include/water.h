/*
 * water.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 9, 2024
 *  Version 3: Merge function of ESP1 & ESP2
 *  Author: Minh Tri
 */

//READ WATER LEVEL//

#ifndef INC_WATER_H_
#define INC_WATER_H_

#include "global.h"

void readWaterLevel(const int* pins, int& sum, int& count, int& level, int& measured, const String& mode, int debugValue, bool isOut);


#endif /* INC_WATER_H_ */