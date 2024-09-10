
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

void apEspSetup(String ssid, uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t* peerMac, wifi_mode_t mode, bool isAp) ;

void serverSetup(AsyncWebServer &server);


#endif
