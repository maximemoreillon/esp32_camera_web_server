// Head partials
// Style
const String styles = "<style>"
  ".main{text-align:center;}"
  ".main img{max-width: 100%;}"
  "</style>";

// Body partials
const String header = "<div class='header'>"
  "ESP32 CAMERA"
  "</div>";

const String nav = "<div class='nav'>"
  "<a href='/'>Home</a>"
  "<a href='/update_form'>Firmware update</a>"
  "</div>";
  
const String footer= "<div class='footer'>"
  "<img src='https://maximemoreillon.com/images/logo/logo.png'>"
  "  <div>"
  "    <div>ESP32 Camera firmware v0.3</div>"
  "    <div>Maxime Moreillon</div>"
  "  </div>"
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
  "<link rel='stylesheet' type='text/css' href='http://maximemoreillon.com/web_components/master_css/master.css'>"
  "</head>";

String pre_main = "<html>"
  + head + 
  "<body>"
  "<div class='wrapper'>"
  + header + nav +
  "<div class='main'>";
  
String post_main = "</div>"
  + footer +
  "</div>"
  "</body>"
  "</html>";

// Root
String root_main = "<h2>Services</h2>"
  "<a href='/frame'>Frame</a><br><br>"
  "<a href='/stream'>Stream</a><br><br>";
  
// Not found
String not_found = "<h2>Not found</h2>";
