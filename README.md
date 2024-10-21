# Damp-Controller-PlatformIO

## Introduction
Damp controller using ESP32 to measure water heights and connect to a mobile device to control via Access Point.

## Guide
### Upload code: 
```
pio run -e esp32dev1 -e esp32dev2 --target upload
```

### Upload code via OTA:
- Both:
```
./upload_ota.sh
```
- ESP1:
```
pio run -e esp32dev1 --target upload --upload-port 192.168.1.1
```
- ESP2:
```
pio run -e esp32dev1 --target upload --upload-port 192.168.1.2
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
