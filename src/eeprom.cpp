/*
 * eeprom.cpp
 *
 *  Created on: Sep 9, 2024
 *  Last modified: Oct 11, 2024
 *  Version 1: Init
 *  Version 2: Added reset EEPROM values
 *  Author: Minh Tri
 */

//USING EEPROM TO SAVE ESP32 VALUE//

#include "eeprom.h"

void eepromSetup(){
    preferences.begin("storage", false);
    h1 = preferences.getInt("h1", -1);
    h2 = preferences.getInt("h2", -1);
    isBot = preferences.getInt("isBot", 1);
    debugIn = preferences.getInt("debugIn", -1);
    debugOut = preferences.getInt("debugOut", -1);
    wifiPass = preferences.getString("wifiPass", "dapsontien");
    adminPass = preferences.getString("adminPass", "quanlydap");
}

void resetEEPROM() {
    preferences.clear();

    preferences.putInt("h1", -1);
    preferences.putInt("h2", -1);
    preferences.putInt("isBot", 1);
    preferences.putInt("debugIn", -1);
    preferences.putInt("debugOut", -1);
    preferences.putString("wifiPass", "dapsontien");
    preferences.putString("adminPass", "quanlydap");

    gateMode = "MANUAL";
    gateStatus = "FORCE_CLOSE";
    motorStatus = "OFF";

    preferences.end();

    eepromSetup();
}


void updateEeprom(String type, int value, String stringValue){
    if (type == "h1") preferences.putInt("h1", value);
    else if (type == "h2") preferences.putInt("h2", value);
    else if (type == "isBot") preferences.putInt("isBot", value);
    else if (type == "debugIn") preferences.putInt("debugIn", value);
    else if (type == "debugOut") preferences.putInt("debugOut", value);
    else if (type == "wifiPass") preferences.putString("wifiPass", stringValue);
    else if (type == "adminPass") preferences.putString("adminPass", stringValue);
}