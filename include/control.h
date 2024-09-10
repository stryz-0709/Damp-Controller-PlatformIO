/*
 * control.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 9, 2024
 *  Version 3: Remove Automatic gate control
 *  Author: Minh Tri
 */

///GATE CONTROL - OPEN, CLOSE & FORCE_CLOSE///

#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#include "global.h"

void closingGate();

void openingGate(String mode);

void forceClose();

#endif /* INC_CONTROL_H_ */