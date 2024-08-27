#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 

IPAddress apIP(55, 55, 55, 55); 

const char* src_ssid = "Table"; //שם הרשת
ESP8266WebServer server(80); 


void WifiSetup(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00   
  WiFi.softAP(src_ssid); 
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin(); 

}

void WifiServer_loop() {
  server.handleClient();//.server is defined at this tab
  delay(10);
} 



void handleRoot() {

  String html = "<html><head><title>Performance Table</title></head><body>";
  html += "<center><h1>Your Performance Table</h1>";
  html += "<table border='1'><tr><th>Index</th><th>Duration</th><th>Is Improve</th></tr>";
  for (int i = 0; i < recordIndex ; i++) {
    html += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressRecords[i]) + "</td><td>" + (isRecordNew[i] ? "Yes" : "No") + "</td></tr>";
  }
  html += "</table></center></body></html>";

  server.send(200, "text/html", html);
}



void handleNotFound(){
  String message = "File Not Found \n \n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

