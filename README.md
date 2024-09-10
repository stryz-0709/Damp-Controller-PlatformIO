# ESP32_DAMP_CONTROLLER

## Introduction
Damp controller using ESP32 to measure water heights and connect to a mobile device to control via Access Point.

## Guide
### Upload code: 
```
pio run -e esp32dev1 -e esp32dev2 --target upload
```
### Monitor - Open 2 terminal windows:
- ESP1: 
```
pio device monitor -e esp32dev1
```
- ESP2:
```
pio device monitor -e esp32dev2
```