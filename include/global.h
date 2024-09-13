/*
 * global.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 2: Added EEPROM
 *  Version 3: Added support for ArduinoOTA
 *  Version 3.1: Added global variables for toggling tower led
 *  Author: Minh Tri
 */

//GLOBAL VARIABLES INITIALIZATIONS//

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <esp_now.h>
#include <Preferences.h>


#include "control.h"
#include "helper.h"
#include "logic.h"
#include "motor.h"
#include "print.h"
#include "espserver.h"
#include "eeprom.h"
#include "water.h"


///WATER SENSOR PINS - PULLED_UP///
#define OUT1 23
#define OUT2 22
#define OUT3 21
#define OUT4 19
#define OUT5 18
#define OUT6 5
#define OUT7 17
//////////
#define IN1 23
#define IN2 22
#define IN3 21
#define IN4 19
#define IN5 18
#define IN6 5
#define IN7 17

///GATE SWITCHES - PULLED_DOWN///
#define GATE_TOP 14
#define GATE_BOTTOM 13

///VALVES - OUTPUT///
#define VALVE_UP 26
#define VALVE_DOWN 33

///MANUAL SWITCH - PULLED_UP///
#define END_BUTTON 27
#define GET_WATER 4
#define REMOVE_WATER 15

///LED///
#define GET_WATER_LED 4
#define REMOVE_WATER_LED 16

#define TOWER_LED 13

#define START_BUTTON 15

///MOTOR - OUTPUT//
#define MOTOR_TRIG 32
#define MOTOR 16

extern AsyncWebServer server;
extern Preferences preferences;

typedef struct struct_message {
  int value;
} struct_message;

extern struct_message dataEsp1;
extern struct_message dataEsp2;

extern esp_now_peer_info_t peerInfo;

extern int IN_PINS[7], OUT_PINS[7], ESP1_OUTPUTS[4], ESP2_OUTPUTS[4], SWITCHES[5];

extern String gateStatus, gateMode, motorStatus, errorCode, pendingMessage;

//ESP32 MAC Address///
extern uint8_t esp1Mac[];
extern uint8_t esp2Mac[];

extern IPAddress esp1IP, esp2IP, NMask;
extern String ssid;

extern AsyncWebServerRequest *pendingRequest;

extern unsigned long prevWaterMillis, prevWater2Millis, prevGateMillis, 
  motorStandbyMillis, motorTrigMillis, prevButtonMillis, sendMobileMillis, towerToggleMillis;

extern const long buttonInterval, waterInterval,
  countInterval, gateInterval, motorTrigInterval,
  motorOnInterval, standByInterval, botInterval, sendMobileInterval, towerToggleInterval; 

extern unsigned long motorDelayMillis, prevBotMillis;

extern bool closingPhase, outToIn, inToOut, toggleTowerLed;

extern int outMeasured, inMeasured, h1, h2, top_val, bot_val;

extern int water1Count, water2Count, gateCount;

extern int outSum, outLevel, inSum, inLevel, isBot, debugOut, debugIn;

extern int endButton, getWater, removeWater, prevEndButton, prevGetWater, prevRemoveWater;


#endif /* INC_GLOBAL_H_ */