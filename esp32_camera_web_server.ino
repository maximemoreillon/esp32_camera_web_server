/*
 * Board type: ESP32 WROVER
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

#include "camera_pins.h"

//Device info
#define DEVICE_TYPE "camera"
#define DEVICE_FIRMWARE_VERSION "0.2.1"


IotKernel iot_kernel(DEVICE_TYPE,DEVICE_FIRMWARE_VERSION); 



void setup() {
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("ESP32 Camera web server");
  
  camera_init();
  iot_kernel.init();
  http_config();
  
}

void loop() {
  iot_kernel.loop();
}
