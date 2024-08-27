#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "ayala5";
const char* pswd = "0537254180";


WiFiClient client;
int server_port = 80;
// פונקציה לבדיקה וחיבור לרשת ה-WiFi
void wifiClient_Setup(){  
  Serial.println("wifiSetup");
  WiFi.begin(ssid,pswd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("trying ...");
        delay(100);
    }
    Serial.println("Connected to network"); // הודעה על חיבור מוצלח
}




int GetData() {
    int ret = -1;
    HTTPClient http;
    String dataURL = "http://api.kits4.me/GEN/api.php?";
    dataURL += "ACT=GET&DEV=11&CH=1";
    http.begin(client, dataURL);
    int httpCode = http.GET();
   
    Serial.print("HTTP code: ");
    Serial.println(httpCode);
   
    if (httpCode == HTTP_CODE_OK) {
        Serial.print("HTTP response code: ");
        Serial.println(httpCode);
        String Res = http.getString(); // קבלת תגובת השרת
        Serial.print("Response from server: ");
        Serial.println(Res); // הדפסת תגובת השרת
        ret = Res.toInt(); // המרת התגובה למספר ושמירתו
    } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpCode); // הדפסת שגיאה אם הבקשה נכשלה
        Serial.println("Check if the server is up and URL is correct."); // הדפסת הודעת שגיאה נוספת
    }
    http.end(); // סיום הבקשה
    return ret; // החזרת הערך שהתקבל מהשרת
}






void SetNewRecordToServer(unsigned long newRecord) {
    HTTPClient http; // יצירת אובייקט HTTPClient לפניות HTTP
    String dataURL = "http://api.kits4.me/GEN/api.php?"; // הגדרת כתובת ה-API
    dataURL += "ACT=SET&DEV=11&CH=1&VAL=";
    dataURL += String(newRecord); // הוספת הערך החדש לכתובת ה-URL
    Serial.print("Sending new record: ");
    Serial.println(newRecord); // הדפסת הערך הנשלח
    http.begin(client, dataURL); // התחלת בקשת GET לשרת עם הערך החדש
    int httpCode = http.GET(); // קבלת קוד התגובה מהשרת
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("New record sent successfully."); // הודעה על הצלחה בשליחת השיא החדש
    } else {
        Serial.print("Error sending new record: ");
        Serial.println(httpCode); // הדפסת הודעת שגיאה אם הבקשה נכשלה
    }
    http.end(); // סיום הבקשה
}









