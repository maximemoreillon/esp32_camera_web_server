/*
 * Board type: ESP32 WROVER
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>
#include "esp_camera.h"

#include "credentials.h"


#include "pin_mapping_ai_thinker.h"
//#include "pin_mapping_t-journal.h"
//#include "pin_mapping_t-camera.h"
//#include "pin_mapping_t-camera_plus.h"

//Device info
#define DEVICE_TYPE "esp32-camera-server"
#define DEVICE_FIRMWARE_VERSION "0.1.1"

// Misc
#define U_PART U_SPIFFS // Needed for OTA updates


AsyncWebServer server(80);


void setup() {
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("ESP32 Camera web server");
  
  wifi_setup();   
  server_init();
  camera_init();
}

void loop() {
  
}
