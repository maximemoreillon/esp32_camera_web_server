// Head partials
// Style
const String styles = "<style>"
  "body{text-align: center;}"
  "body > * {margin: 20px;}"
  ".nav a {margin: 0 10px;}"
  "</style>";

// Body partials
const String header = "<div class='header'><h1>ESP32 CAMERA</h1></div>";

const String nav = "<div class='nav'>"
  "  <a href='/'>Home</a>"
  "  <a href='/update_form'>Firmware update</a>"
  "  <a href='/frame'>Frame</a>"
  "  <a href='/stream'>Stream</a>"
  "</div>";
  
const String footer= "<div class='footer'>"
  "  <div>ESP32 Camera firmware</div>"
  "  <div>Maxime MOREILLON</div>"
  "</div>";

// Update form
String update_form = "<h2>Firmware update</h2>"
  "<form method='POST' action='/update' enctype='multipart/form-data'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>";

// Combinations
String head ="<head>"
  "<title>ESP32 camera</title>"
  + styles +
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "</head>";

String pre_main = "<html>"
  + head + 
  "<body>"
  + header + nav +
  "<div class='main'>";
  
String post_main = "</div>"
  + footer +
  "</div>"
  "</body>"
  "</html>";
    
// Not found
String not_found = "<h2>Not found</h2>";
