/*
 * Board type: AI Thinker ESP32-CAM (the generic "ESP32-CAM" modules sold on AliExpress)
 * Partition scheme: "Regular 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)", needed for OTA and LittleFS
 * NOTE: the board's default "Huge APP" partition scheme has no OTA
 */

#include "IotKernel.h"
#include "esp_camera.h"

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
//#define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
//#define CAMERA_MODEL_TTGO_T_CAMERA_PLUS

#include "camera_pins.h"

//Device info
#define DEVICE_TYPE "camera"
#define DEVICE_FIRMWARE_VERSION "0.3.0"


IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 

bool camera_ready = false;



void setup() {
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("ESP32 Camera web server");
  
  // NOTE: the kernel is started even if the camera fails so that the device remains reachable for OTA updates
  camera_ready = camera_init();
  if(!camera_ready) Serial.println("[CAMERA] Not available, /frame and /stream will respond with 503");
  iot_kernel.init();
  http_config();
  
}

void loop() {
  iot_kernel.loop();
}
