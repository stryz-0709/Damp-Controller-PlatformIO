/*
 * eeprom.h
 *
 *  Created on: Sep 9, 2024
 *  Last modified: Sep 9, 2024
 *  Version 1: Init
 *  Author: Minh Tri
 */

//USING EEPROM TO SAVE ESP32 VALUE//

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "global.h"

void eepromSetup();

void resetEEPROM();

void updateEeprom(String type, int value, String stringValue);


#endif