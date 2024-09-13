/*
 * global.cpp
 *
*  Created on: Aug 26, 2024
 *  Last modified: Sep 13, 2024
 *  Version 2: Added EEPROM
 *  Version 3: Added support for ArduinoOTA
 *  Version 3.1: Added global variables for toggling tower led
 *  Author: Minh Tri
 */

//GLOBAL VARIABLES INITIALIZATIONS//

#include "global.h"

int IN_PINS[7] = { IN1, IN2, IN3, IN4, IN5, IN6, IN7 };
int OUT_PINS[7] = { OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7 };

int ESP1_OUTPUTS[4] = { VALVE_UP, VALVE_DOWN, MOTOR_TRIG, MOTOR };
int SWITCHES[5] = { GATE_TOP, GATE_BOTTOM, GET_WATER, REMOVE_WATER, END_BUTTON };

int ESP2_OUTPUTS[4] = { GET_WATER_LED, REMOVE_WATER_LED, START_BUTTON, TOWER_LED };

////////////
// AsyncWebServer esp32server(80);

AsyncWebServerRequest *pendingRequest = nullptr;

esp_now_peer_info_t peerInfo;

struct_message dataEsp1;
struct_message dataEsp2;

IPAddress esp1IP(192, 168, 1, 1);
IPAddress esp2IP(192, 168, 1, 2);
IPAddress NMask(255, 255, 255, 0);
String ssid = "Cổng 1";

String pendingMessage;
Preferences preferences;

unsigned long prevWaterMillis = 0;
unsigned long prevWater2Millis = 0;
unsigned long prevGateMillis = 0;
unsigned long motorStandbyMillis = 0;
unsigned long towerToggleMillis = 0;

unsigned long prevButtonMillis = 0;
const long buttonInterval = 200;

const long towerToggleInterval = 1000;

const long waterInterval = 500;
const long countInterval = 10;   //500ms*10 = 5 seconds

const long gateInterval = 200;  //200ms

const long motorOnInterval = 10000; //Turn on motor for 10 seconds
const long motorTrigInterval = 3000; 
const long standByInterval = 180000; ////Standby motor for 3 minutes
unsigned long motorDelayMillis = 0;
unsigned long motorTrigMillis = 0;

unsigned long prevBotMillis = 0;
const long botInterval = 21000;  ///21s before stopping gate

unsigned long sendMobileMillis = 0;
const long sendMobileInterval = 1000;

bool closingPhase = false;
bool outToIn = false;
bool inToOut = false;
bool toggleTowerLed = true;

int outMeasured = 0;
int inMeasured = 0;

int h1 = 1;
int h2 = 1;

int top_val = 0;
int bot_val = 0;

int water1Count = 0;
int water2Count = 0;
int gateCount = 0;

String gateStatus = "STOPPED"; //STOPPED, OPENING, CLOSING, GET_WATER, REMOVE_WATER, STANDBY, FORCE_CLOSE
String gateMode = "MANUAL"; //MANUAL, END, DEBUG
String motorStatus = "OFF"; //OFF, TRIGGERED, DELAY, ACTIVE, STANDBY

int outSum = 0;
int outLevel = 0;
int inSum = 0;
int inLevel = 0;
int isBot = 0;
int debugOut = 0;
int debugIn = 0;

int endButton = 0;
int getWater = 0;
int removeWater = 0;

int prevEndButton = 0;
int prevGetWater = 0;
int prevRemoveWater = 0;

String errorCode = "";


//ESP32 MAC Address///
///Change with different ESP32s///
uint8_t esp1Mac[] = { 0x10, 0x06, 0x1C, 0x85, 0x81, 0x28 };
uint8_t esp2Mac[] = { 0x58, 0xBF, 0x25, 0x8C, 0x2B, 0xF4 };
