/*
 * global.h
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 2: Added EEPROM
 *  Version 3: Added support for ArduinoOTA
 *  Version 3.1: Added global variables for toggling tower led
 *  Version 3.2: Revert toggling function
 *  Author: Minh Tri
 */

//GLOBAL VARIABLES INITIALIZATIONS//

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <ArduinoOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <esp_now.h>
#include <WebSerial.h>
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
#define OUT1 14
#define OUT2 13
#define OUT3 12
#define OUT4 11
#define OUT5 10
#define OUT6 9
#define OUT7 8
//////////
#define IN1 18
#define IN2 17
#define IN3 16
#define IN4 15
#define IN5 7
#define IN6 6
#define IN7 5

///GATE SWITCHES - PULLED_DOWN///
#define GATE_TOP 2
#define GATE_BOTTOM 1

///VALVES - OUTPUT///
#define VALVE_UP 41
#define VALVE_DOWN 42

///MANUAL SWITCH - PULLED_UP///
#define END_BUTTON 40
#define START_BUTTON 39

#define GET_WATER 37
#define REMOVE_WATER 38

///LED///
#define GET_WATER_LED 35
#define REMOVE_WATER_LED 36

#define TOWER_LED 4

///MOTOR - OUTPUT//
#define MOTOR_TRIG 21
#define MOTOR 47

#define ESP_LED 48
#define ESP_BUTTON 45

extern AsyncWebServer serverEsp1;
extern Preferences preferences;

typedef struct struct_message {
  int value;
} struct_message;

extern int IN_PINS[7], OUT_PINS[7], ESP_OUTPUTS[8], SWITCHES[2], BUTTONS[3];

extern String gateStatus, gateMode, motorStatus, errorCode, pendingMessage;

extern IPAddress esp1IP, NMask, startIP, endIP;
extern String ssid;
extern String wifiPass, adminPass;

extern AsyncWebServerRequest *pendingRequest;

extern unsigned long prevWaterMillis, prevGateMillis, 
  motorStandbyMillis, motorTrigMillis, prevButtonMillis, sendMobileMillis, startUpMillis,
  motorDelayMillis, prevBotMillis;

extern const long buttonInterval, waterInterval,
  countInterval, gateInterval, motorTrigInterval,
  motorOnInterval, standByInterval, startUpInterval, botInterval, sendMobileInterval; 


extern bool closingPhase, startUp, outToIn, inToOut, turnOff;

extern int outMeasured, inMeasured, h1, h2, top_val, bot_val;

extern int waterCount, gateCount;

extern int outSum, outLevel, inSum, inLevel, isBot, debugOut, debugIn;

extern int endButton, getWater, removeWater, prevEndButton, prevGetWater, prevRemoveWater, builtInButton;


#endif /* INC_GLOBAL_H_ */