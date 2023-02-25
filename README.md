# ESP32 Camera web server (Async)

A firmware for ESP32 camera boards which allows the serving of frames or streams via an asynchronous web server.
The firmware also allows updated via the provided web interface.
The frame and stream serving logic is based Me-no-dev's code, available at https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3

## Requirements and dependencies

This sketch requires the ESP32 core for Arduino asd well as the [IoT Kernel](https://github.com/maximemoreillon/iot-kernel) library.

## Usage

1. Upload static files to the LittleFS of the ESP32
2. Upload the sketch
3. Connect to the access point of camera to configure the Wifi connection
