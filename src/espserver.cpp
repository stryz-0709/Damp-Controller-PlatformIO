/*
 * espserver.cpp
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

  //ON if value == 1, else OFF
  digitalWrite(GET_WATER_LED, dataEsp2.value == 1 ? HIGH : LOW);  

  //ON if value == 2, else OFF
  digitalWrite(REMOVE_WATER_LED, dataEsp2.value == 2 ? HIGH : LOW); 

  //RELAYS, TURN OFF if value == 4, else ACTIVE
  digitalWrite(START_BUTTON, dataEsp2.value == 0 ? HIGH : LOW);     

}


////////////////
void OnEsp1DataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}
void OnEsp2DataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}


////////////////
void sendLedInfo(int led){
  dataEsp1.value = led;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(esp2Mac, (uint8_t *)&dataEsp1, sizeof(dataEsp1));

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
  esp_err_t result = esp_now_send(esp1Mac, (uint8_t *)&dataEsp2, sizeof(dataEsp2));

  if (result == ESP_OK){
    Serial.print("Sent value: ");
    Serial.println(value);
  }
  else {}
}

void recvMsg(uint8_t *data, size_t len){
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
  if (d.startsWith("!") && d.endsWith("#")) {
    String command = d.substring(1, d.length() - 1);

    int separatorIndex = command.indexOf('=');
    if (separatorIndex != -1) {
      String parameter = command.substring(0, separatorIndex);
      String value = command.substring(separatorIndex + 1);
      
      if (parameter == "h1") {
        h1 = value.toInt(); 
      }
      else if (parameter == "h2"){
        h2 = value.toInt();
      }
    }
  }
}



////////////////
void apEspSetup(uint8_t* peerMac, wifi_mode_t mode) {
  bool isAp = (mode == WIFI_AP_STA);
  Serial.println("Configuring device...");

  // Set Wi-Fi mode (AP+STA for ESP1, STA for ESP2)
  WiFi.mode(mode);
  delay(1000);

  if (isAp) {  // For ESP1 acting as Access Point
    WiFi.softAP(ssid.c_str());
    Serial.println("Wait 100 ms for AP_START...");
    delay(100);

    Serial.println("Set softAPConfig");
    WiFi.softAPConfig(esp1IP, esp1IP, NMask);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);  // Stop the default DHCP server

    tcpip_adapter_ip_info_t info;
    info.ip.addr = static_cast<uint32_t>(esp1IP);
    info.gw.addr = static_cast<uint32_t>(esp1IP);   // Gateway is the same as ESP1's IP
    info.netmask.addr = static_cast<uint32_t>(NMask);
    tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info);

    // Set DHCP lease range
    dhcps_lease_t lease;
    lease.enable = true;
    lease.start_ip.addr = static_cast<uint32_t>(startIP);
    lease.end_ip.addr = static_cast<uint32_t>(endIP);
    tcpip_adapter_dhcps_option(TCPIP_ADAPTER_OP_SET, TCPIP_ADAPTER_REQUESTED_IP_ADDRESS, &lease, sizeof(dhcps_lease_t));

    // Restart DHCP server
    tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);

    ///ARDUINO OTA
    ArduinoOTA.setHostname("mainOTA"); 
    ArduinoOTA.setPassword(""); 
    ArduinoOTA.begin();
  }
  else{
    WiFi.config(esp2IP, esp1IP, NMask);
    WiFi.begin(ssid, "");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    ArduinoOTA.setHostname("auxOTA"); 
    ArduinoOTA.setPassword(""); 
    ArduinoOTA.begin();
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
  WebSerial.begin(&server);
  WebSerial.msgCallback(recvMsg);
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
