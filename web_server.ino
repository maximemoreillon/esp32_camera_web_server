void web_server_setup(){
  Serial.println(F("[Web server] Web server initialization"));

  web_server.on("/", handle_root);
  web_server.on("/stream", HTTP_GET, handle_stream);
  web_server.on("/frame", HTTP_GET, handle_frame);
  web_server.on("/update_form", handle_update_form);
  web_server.on("/update",HTTP_POST, handle_update, handle_update_upload);
 
  web_server.onNotFound(handle_not_found);
  web_server.begin();
}

void handle_stream(void) {

  // Initialize an empty frame buffer
  camera_fb_t * fb = NULL;
  
  // Sending response header
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Access-Control-Allow-Origin: *\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n;";
  web_server.sendContent(response);

  // Sending actual content
  WiFiClient client = web_server.client();

  while (client.connected()) {
    
    // Frame capture
    fb = esp_camera_fb_get();
      
    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n\r\n";
    web_server.sendContent(response);

    client.write((char *)fb->buf, fb->len);
    
    web_server.sendContent("\r\n");

    // Empty the buffer
    if(fb) {
      esp_camera_fb_return(fb);
      fb = NULL;
    }
  }
}


void handle_frame(void) {
  
  WiFiClient client = web_server.client();

  // Initialize an empty frame buffer
  camera_fb_t * fb = NULL;

  // Frame capture
  fb = esp_camera_fb_get();

  // Send response header
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Access-Control-Allow-Origin: *\r\n";
  response += "Content-disposition: inline; filename=capture.jpg\r\n";
  response += "Content-type: image/jpeg\r\n\r\n";
  web_server.sendContent(response);
  
  // Send frame
  client.write((char *)fb->buf, fb->len);
  
  // Empty the buffer
  if(fb) {
    esp_camera_fb_return(fb);
    fb = NULL;
  }
}


void handle_update_form(){
  String html = pre_main + update_form + post_main;
  web_server.sendHeader("Connection", "close");
  
  web_server.send(200, "text/html", html);
}

void handle_update(){
  String upload_status;
  if(Update.hasError()){
    upload_status = "Upload failed";
  }
  else {
    upload_status = "Upload success";
  }
  String html = pre_main + upload_status + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.send(200, "text/html", html);
  ESP.restart();
  
}

void handle_update_upload() {
  HTTPUpload& upload = web_server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.setDebugOutput(true);
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin()) { //start with max available size
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
      Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
    Serial.setDebugOutput(false);
  }
}

void handle_not_found() {
  String html = pre_main + not_found + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.send(200, "text/html", html);
}

void handle_root() {
  String html = pre_main + root_main + post_main;
  web_server.sendHeader("Connection", "close");
  web_server.send(200, "text/html", html);
}
