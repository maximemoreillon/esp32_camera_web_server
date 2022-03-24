# ESP32 Camera web server (Async)

A firmware for ESP32 camera boards which allows the serving of frames or streams via an asynchronous web server.
The firmware also allows updated via the provided web interface.
The frame and stream serving logic is based Me-no-dev's code, available at https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3

## Requirements and dependencies

This sketch requires version 2.x of the ESP32 core for Arduino.

In order to upload static files served by the web server, the [Arduino ESP32 filesystem uploader](https://github.com/lorol/arduino-esp32fs-plugin) must be installed.

Moreover, the following libraries are needed:

* [PubSubClient](https://github.com/knolleary/pubsubclient/releases/tag/v2.8)
* [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)


## Usage

1. Upload static files to the LittleFS of the ESP32
2. Upload the sketch
3. Connect to the access point of camera to configure the Wifi connection