  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiUdp.h>
  #include <ESP8266HTTPClient.h>

const char* ssid = "ayala5";
const char* pswd = "0537254180";

WiFiClient client; //מגדיר את האובייקט להתחברות על הרשת בתוך קליינט
int server_port = 80; //http אם זה אז מתחבר בפורט 80

void wifiClient_Setup(){  //פונקציה אשר בודקת אם התחברתי וכל עוד לא התחברתי אז מנסה להתחבר עד שמצליח
  Serial.println("wifiSetup");
  WiFi.begin(ssid,pswd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("trying ...");
        delay(100);
    }
    Serial.println("Connected to network");
}


int GetData() {
    int ret = -1;
    HTTPClient http;
    String dataURL = "http://api.kits4.me/GEN/api.php?";
    dataURL += "ACT=GET&DEV=11&CH=1";
    http.begin(client, dataURL); 
    int httpCode = http.GET();
    
    Serial.print("HTTP code: ");
    Serial.println(httpCode); // הדפסת קוד HTTP שהתקבל
    
    if (httpCode == HTTP_CODE_OK) {
        Serial.print("HTTP response code: ");
        Serial.println(httpCode);
        String Res = http.getString(); 
        Serial.print("Response from server: ");
        Serial.println(Res); // הדפסת תגובת השרת
        ret = Res.toInt(); 
    } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpCode);
        Serial.println("Check if the server is up and URL is correct.");
    }
    http.end();
    return ret;
}



void SetNewRecordToServer(unsigned long newRecord) {
    HTTPClient http;
    String dataURL = "http://api.kits4.me/GEN/api.php?";
    dataURL += "ACT=SET&DEV=11&CH=1&VAL=";
    dataURL += String(newRecord); // הוספת הערך החדש לכתובת ה-URL
    Serial.print("Sending new record: ");
    Serial.println(newRecord); // הדפסת הערך הנשלח
    http.begin(client, dataURL); // מאתחל פנייה לשרת עם הכתובת
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        Serial.println("New record sent successfully.");
    } else {
        Serial.print("Error sending new record: ");
        Serial.println(httpCode);
    }
    http.end(); // סוגר את הפנייה לשרת
}

