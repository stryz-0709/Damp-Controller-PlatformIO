/*
 * espserver.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 9, 2024
 *  Version 3: Merge functions of ESP1 & ESP2
 *  Author: Minh Tri
 */

//AP, ESP_NOW & SERVER SETUP//

#include "espserver.h"

////////////////
void OnEsp1DataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&dataEsp1, incomingData, sizeof(dataEsp1));
  inLevel = (gateMode == "DEBUG")? debugIn : dataEsp1.value;
  Serial.print("Received value: ");
  Serial.println(dataEsp1.value);
  inMeasured = 1;
}

void OnEsp2DataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  memcpy(&dataEsp2, incomingData, sizeof(dataEsp2));
  Serial.print("Received value: ");
  Serial.println(dataEsp2.value);
  digitalWrite(GET_WATER_LED, dataEsp2.value == 1 ? HIGH : LOW);
  digitalWrite(REMOVE_WATER_LED, dataEsp2.value == 2 ? HIGH : LOW);
  digitalWrite(START_BUTTON, dataEsp2.value == 3 ? HIGH : LOW);
}


////////////////
void OnEsp1DataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}
void OnEsp2DataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}


////////////////
void sendLedInfo(int led){
  dataEsp1.value = led;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(esp2, (uint8_t *)&dataEsp1, sizeof(dataEsp1));

  if (result == ESP_OK){
    Serial.print("Sent value: ");
    Serial.println(led);
  }
  else {}
}

////////////////
void sendWaterInfo(int value){
  dataEsp2.value = value;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(esp1, (uint8_t *)&dataEsp2, sizeof(dataEsp2));

  if (result == ESP_OK){
    Serial.print("Sent value: ");
    Serial.println(value);
  }
  else {}
}

////////////////
void apEspSetup(String ssid, uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t* peerMac, wifi_mode_t mode, bool isAp) {
  Serial.println("Configuring device...");

  // Set Wi-Fi mode (AP+STA for ESP1, STA for ESP2)
  WiFi.mode(mode);
  delay(1000);

  if (isAp) {  // For ESP1 acting as Access Point
    WiFi.softAP(ssid.c_str());
    Serial.println("Wait 100 ms for AP_START...");
    delay(100);

    Serial.println("Set softAPConfig");
    IPAddress Ip(a, b, c, d);
    IPAddress NMask(255, 255, 255, 0);
    WiFi.softAPConfig(Ip, Ip, NMask);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callbacks for sending and receiving data
  esp_now_register_send_cb(isAp? OnEsp1DataSent : OnEsp2DataSent);
  esp_now_register_recv_cb(isAp? OnEsp1DataRecv : OnEsp2DataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, peerMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW Peer added successfully");
}



////////////////
void serverSetup(AsyncWebServer &server) {
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("body", true)) {
      pendingMessage = request->getParam("body", true)->value();
      Serial.println("Received message: " + pendingMessage);
      
      decodePendingMessage(pendingMessage);
    }
    else pendingMessage = "No message received";
    pendingRequest = request;
  });

  server.on("/getWaterInfo", HTTP_GET, [](AsyncWebServerRequest *request) {
    pendingRequest = request;
  });

  server.begin();
}

////////////////
void sendToAndroid(){
  if (pendingRequest) {
    JsonDocument doc;

    doc["inLevel"] = inLevel;
    doc["outLevel"] = outLevel;
    doc["h1"] = h1;
    doc["h2"] = h2;
    doc["top_val"] = top_val;
    doc["bot_val"] = isBot;
    doc["gateStatus"] = gateStatus;
    doc["gateMode"] = gateMode;
    doc["errorCode"] = errorCode;

    Serial.println("Sent to device");

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    pendingRequest->send(200, "application/json", jsonResponse);
    pendingRequest = nullptr;
  }
}
