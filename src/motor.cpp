/*
 * motor.cpp
 *
 *  Created on: Aug 26, 2024
 *  Last modified: Aug 26, 2024
 *  Version 1: Init
 *  Author: Minh Tri
 */

//CONTROLLING STATES OF MOTOR//


#include "motor.h"

void activateMotor(){
  digitalWrite(MOTOR, LOW);
  motorTrigMillis = millis();
  motorStatus = "TRIGGERED";
}

void triggerMotor(){
  digitalWrite(MOTOR_TRIG, LOW);
  motorDelayMillis = millis();
  motorStatus = "DELAY";
}

void deactivateMotor(){
  digitalWrite(MOTOR_TRIG, HIGH);
  digitalWrite(MOTOR, HIGH);
  motorStatus = "OFF";
}

void activateStandby(){
  motorStandbyMillis = millis();
  motorStatus = "STANDBY";
}