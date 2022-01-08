void camera_init(){
  camera_config_t config;
  
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  
  config.pin_d0 = D0_GPIO_NUM;
  config.pin_d1 = D1_GPIO_NUM;
  config.pin_d2 = D2_GPIO_NUM;
  config.pin_d3 = D3_GPIO_NUM;
  config.pin_d4 = D4_GPIO_NUM;
  config.pin_d5 = D5_GPIO_NUM;
  config.pin_d6 = D6_GPIO_NUM;
  config.pin_d7 = D7_GPIO_NUM;
  
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Frame parameters
  config.frame_size = FRAMESIZE_UXGA;
  //config.frame_size = FRAMESIZE_SXGA;
  //config.frame_size = FRAMESIZE_XGA;
  //config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("[CAMERA] init failed with error 0x%x", err);
    return;
  }

  Serial.println("[CAMERA] init OK");

  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_VGA);
}
