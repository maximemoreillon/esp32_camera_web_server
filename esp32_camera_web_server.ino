#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <Update.h>

/*
 * BOARD SETTINGS
 * 
 * Board type: ESP32 Wrover Module
 * 
 */

// Getting WIFI_SSID and WIFI_PASSWORD from external credentials file
#include "jtektiot_credentials.h";

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
