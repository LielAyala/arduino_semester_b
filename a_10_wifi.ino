#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 

IPAddress apIP(55, 55, 55, 55); // הגדרת כתובת IP של נקודת הגישה

const char* src_ssid = "Table"; //שם הרשת
ESP8266WebServer server(80); 
void WifiSetup(){
  WiFi.mode(WIFI_AP_STA); 
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
  WiFi.softAP(src_ssid);
  server.on("/", handleRoot); 
  server.onNotFound(handleNotFound); 
  server.begin();
}

void WifiServer_loop() {
  server.handleClient(); 
  delay(10); // המתנה קצרה בין בדיקות
} 


void handleRoot() {
  String html = "<html><head><title>Performance Table</title></head><body>";
  html += "<center><h1>Your Performance Table</h1>"; // יצירת כותרת 
  html += "<table border='1'><tr><th>Index</th><th>Duration</th><th>Is Improve</th></tr>";
  for (int i = 0; i < recordIndex ; i++) {
    html += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressRecords[i]) + "</td><td>" + (isRecordNew[i] ? "Yes" : "No") + "</td></tr>"; // יצירת שורה בטבלה עבור כל לחיצה
  }
  html += "</table></center></body></html>"; // סיום יצירת הטבלה והדף

  server.send(200, "text/html", html); // שליחת תוכן HTML ללקוח
}

// שליחת הודעת שגיאה 404 ללקוח
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

