/*
 * espserver.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 3: Merge functions of ESP1 & ESP2
 *  Version 4: Added support for ArduinoOTA
 *  Version 4.1: Added logic for toggling tower led
 *  Version 4.2: Revert toggling function
 *  Author: Minh Tri
 */

//AP, ESP_NOW & SERVER SETUP//

#ifndef INC_ESPSERVER_H_
#define INC_ESPSERVER_H_

#include "global.h"

void sendToAndroid();

void apEspSetup() ;

void serverSetup(AsyncWebServer &server);


#endif
