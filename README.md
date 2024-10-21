# Damp-Controller-PlatformIO

## Introduction
Damp controller using ESP32 to measure water heights and connect to a mobile device to control via Access Point.

## Guide
### Setup new ESP32:
Locate to global.cpp and change esp1IP, startIP, endIP, and ssid parameters according to the designated number of the ESP32.
```
IPAddress esp1IP(192, 168, 1, X);

IPAddress startIP(192, 168, 1, X+1);
IPAddress endIP(192, 168, 1, X*11);

String ssid = "Cổng X";
```

### Upload code: 
```
pio run -e esp32-s3 --target upload
```

### Monitor on Terminal:
```
pio device monitor -e esp32-s3
```
