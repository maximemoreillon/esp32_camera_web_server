static void wifi_setup(){

  Serial.print("[Wifi] Wifi connecting to ");
  Serial.println(WIFI_SSID);    

  WiFi.hostname(get_device_name());
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

//  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
//    Serial.print("[Wifi] Connected. IP: ");
//    Serial.println(IPAddress(info.got_ip.ip_info.ip.addr));        
//  },
//      WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
//
//  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
//    Serial.print("[Wifi] Connection lost: ");
//    Serial.println(info.disconnected.reason);
//  },
//    WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
}
