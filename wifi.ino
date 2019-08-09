void wifi_setup() {
  // Settings
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println(F("[WIFI] Connecting..."));
}

void wifi_connection_manager(){

  static int wifi_connected = -1; // 1: connected, 0: disconnected, -1: unknown
  
  if(WiFi.status() != WL_CONNECTED) {
    if(wifi_connected != 0){
      // Wifi connection status changed to "disconnected"
      wifi_connected = 0;
      Serial.println(F("[WiFi] Disconnected"));
    }
  } else {
    if(wifi_connected != 1){
      // Wifi connection status changed to "connected"
      wifi_connected = 1;
      Serial.print(F("[WiFi] Connected, IP: "));
      Serial.println(WiFi.localIP());
    }
  }
  
}
