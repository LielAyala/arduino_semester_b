#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 

IPAddress apIP(55, 55, 55, 55); // הגדרת כתובת IP של נקודת הגישה

const char* src_ssid = "Table"; // שם הרשת של נקודת הגישה
ESP8266WebServer server(80); // יצירת אובייקט שרת על פורט 80

void WifiSetup(){
  WiFi.mode(WIFI_AP_STA); // הגדרת המודול למצב נקודת גישה (AP) ותחנת רשת (STA) במקביל
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // הגדרת תצורת רשת ה-WiFi של נקודת הגישה   
  WiFi.softAP(src_ssid); // יצירת נקודת גישה עם שם הרשת שהוגדר
  server.on("/", handleRoot); // טיפול בבקשה לכתובת הבסיסית של השרת
  server.onNotFound(handleNotFound); // טיפול בבקשות שאינן נמצאות
  server.begin(); // התחלת עבודת השרת
}

void WifiServer_loop() {
  server.handleClient(); // טיפול בבקשות HTTP המגיעות לשרת
}