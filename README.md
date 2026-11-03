# ESP32 Camera web server

A firmware for ESP32 camera boards which serves frames or streams via an asynchronous web server, built on [IoT Kernel](https://github.com/maximemoreillon/iot-kernel).
The frame and stream serving logic is based on Me-no-dev's code, available at https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3

## Endpoints

- `/frame`: a single JPEG image
- `/stream`: an MJPEG stream

If an admin password is set in the settings, these endpoints require HTTP digest authentication (user `admin`).

## Requirements and dependencies

- ESP32 core for Arduino
- [IoT Kernel](https://github.com/maximemoreillon/iot-kernel) 1.0 and its dependencies

## Board

The sketch targets the generic "ESP32-CAM" modules (AI Thinker clones). Other camera models can be selected at the top of `esp32_camera_web_server.ino`.

- Board: AI Thinker ESP32-CAM
- Partition scheme: Regular 4MB with spiffs (1.2MB APP/1.5MB SPIFFS). The board's default "Huge APP" scheme has no OTA.

## Usage

1. Upload static files to the LittleFS of the ESP32
2. Upload the sketch
3. Connect to the access point of camera to configure the Wifi connection
