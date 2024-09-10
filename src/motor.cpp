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