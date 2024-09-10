#include "eeprom.h"

void eepromSetup(){
    preferences.begin("storage", false);
    h1 = preferences.getInt("h1", 1);
    h2 = preferences.getInt("h2", 1);
}


void updateEeprom(int type, int value){
    switch(type){
        case 1:
            preferences.putInt("h1", value);
            break;
        case 2:
            preferences.putInt("h2", value);
            break;
        default:
            break;
    }
}