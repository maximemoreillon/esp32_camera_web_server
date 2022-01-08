/*
 * BOARD SETTINGS
 * Board type: ESP32 Wrover Module
 */

// Libraries
#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <Update.h>


// Getting WIFI_SSID and WIFI_PASSWORD from external credentials file
#include "credentials.h";

//#include "pin_mapping_ai_thinker.h";
#include "pin_mapping_t-journal.h";
//#include "pin_mapping_t-camera.h";
//#include "pin_mapping_t-camera_plus.h";


WebServer web_server(80);


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_init();
  wifi_setup();
  web_server_setup();
}

void loop() {
  wifi_connection_manager();
  web_server.handleClient();
}
