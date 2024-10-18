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
void apEspSetup() {
  Serial.println("Configuring device...");

  // Set Wi-Fi mode (AP+STA for ESP1, STA for ESP2)
  WiFi.mode(WIFI_AP_STA);
  delay(1000);

  WiFi.softAP(ssid.c_str(), wifiPass.c_str());
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


////////////////
void serverSetup(AsyncWebServer &server) {
  // Handle POST request to /post
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("body", true)) {
      pendingMessage = request->getParam("body", true)->value();
      Serial.println("Received message: " + pendingMessage);
      
      decodePendingMessage(pendingMessage);
    }
    else {
      pendingMessage = "No message received";
    }
    pendingRequest = request;
  });

  // Handle GET request to /getWaterInfo
  server.on("/getWaterInfo", HTTP_GET, [](AsyncWebServerRequest *request) {
    pendingRequest = request;
  });

  // Handle POST request for checking password
  server.on("/checkPassword", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("password", true)) {
      pendingMessage = request->getParam("password", true)->value();
      
      request->send(200, "text/plain", 
        (pendingMessage == adminPass)? "success" : "failure");
      
    } 
    else {
      request->send(400, "text/plain", "bad request");
    }
  });

  // Start the server
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
    doc["debugOut"] = debugOut;
    doc["debugIn"] = debugIn;
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
