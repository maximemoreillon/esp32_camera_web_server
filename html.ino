/*
 * This file contains the HTML for the web pages
 * Arguably, storing HTML content as string is not ideal
 */

// Head partials
// CSS
const String styles = ""
  "<style>"
  "body { font-family: Arial, sans-serif; }"
  "nav { display: flex; }"
  "nav a { margin: 0.25em; }"
  "nav a::first-child {margin-left: 0; }"
  "label { display: inline-block; width: 250px; }"
  "th { text-align: left; width: 250px; }"
  "</style>";

String get_html_head() {
  return ""
    "<head>"
    "<title>" + get_device_name() + "</title>"
    + styles +
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "</head>";
}
  

// Body partials
String get_html_header(){
  return ""
    "<header>"
    "  <h1>" + get_device_name() + "</h1>"
    "</header>";
}

const String nav = ""
  "<nav>"
    "<a href='/'>Info</a>"
    "<a href='/stream'>Stream</a>"
    "<a href='/frame'>Frame</a>"
    "<a href='/update'>Firmware update</a>"
  "</nav>";

// Main contents
String get_homepage(){
  return ""
    "<h2>Info</h2>"
    "<table>"
      "<tr><th>Device type</th><td>" + String(DEVICE_TYPE) + "</td></tr>"
      "<tr><th>Device name</th><td>" + get_device_name() + "</td></tr>"
      "<tr><th>Firmware version</th><td>"+ String(DEVICE_FIRMWARE_VERSION) +"</td></tr>"
    "</table>"
    "<h3>Wifi</h3>"
    "<table>"
      "<tr><th>SSID</th><td>" + WIFI_SSID + "</td></tr>"
      "<tr><th>IP</th><td>" + WiFi.localIP().toString() + "</td></tr>"
    "</table>";
}

String firmware_update_form = ""
  "<h2>Firmware update</h2>"
    "<form method='POST' action='/update' enctype='multipart/form-data'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Update'>"
  "</form>";

String firmware_update_success = ""
  "<h2>Firmware update</h2>"
  "<p>Upload successful, rebooting...</p>";

String firmware_update_failure = ""
  "<h2>Firmware update</h2>"
  "<p>Upload failed</p>";
  

String apply_html_template(String main_content){
  return ""
    "<html>"
    + get_html_head() 
    + "<body>"
    + get_html_header()
    + nav 
    + "<main>"
    + main_content
    + "</main>"
    "</body>"
    "</html>";
}
  
