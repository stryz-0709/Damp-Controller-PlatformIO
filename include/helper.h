/*
 * helper.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Aug 26, 2024
 *  Version 1: Init
 *  Author: Minh Tri
 */

//HELPER FUNCTIONS//


#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include "global.h"

void pinSetup();

bool isNumber(String payload);

void backgroundCheck();

bool readInputs();

void decodePendingMessage(String pendingMessage);


#endif