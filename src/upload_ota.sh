#!/bin/bash

ESP32_1_IP="192.168.1.1"  
ESP32_2_IP="192.168.1.2"  

ENV1="esp32dev1"  
ENV2="esp32dev2"  

# Build the project
pio run -e $ENV1 -e $ENV2

# Upload to ESP32 1
pio run -e $ENV1 --target upload --upload-port $ESP32_1_IP
if [ $? -ne 0 ]; then
    echo "Failed to upload to ESP32 1"
    exit 1
fi

# Upload to ESP32 2
pio run -e $ENV2 --target upload --upload-port $ESP32_2_IP
if [ $? -ne 0 ]; then
    echo "Failed to upload to ESP32 2"
    exit 1
fi

echo "Upload completed successfully!"
