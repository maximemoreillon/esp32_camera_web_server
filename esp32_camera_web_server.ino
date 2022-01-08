/*
 * Board type: ESP32 WROVER
 */

#include "IotKernel.h"
#include "esp_camera.h"
#include "pin_mapping_ai_thinker.h"
//#include "pin_mapping_t-journal.h"
//#include "pin_mapping_t-camera.h"
//#include "pin_mapping_t-camera_plus.h"

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
