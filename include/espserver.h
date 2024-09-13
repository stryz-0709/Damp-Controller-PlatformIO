/*
 * espserver.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 3: Merge functions of ESP1 & ESP2
 *  Version 4: Added support for ArduinoOTA
 *  Version 4.1: Added logic for toggling tower led
 *  Author: Minh Tri
 */

//AP, ESP_NOW & SERVER SETUP//

#ifndef INC_ESPSERVER_H_
#define INC_ESPSERVER_H_

#include "global.h"

void OnEsp1DataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void OnEsp2DataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

void OnEsp1DataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnEsp2DataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void sendLedInfo(int led);

void sendWaterInfo(int value);

void sendToAndroid();

void apEspSetup(uint8_t* peerMac, wifi_mode_t mode) ;

void serverSetup(AsyncWebServer &server);


#endif
