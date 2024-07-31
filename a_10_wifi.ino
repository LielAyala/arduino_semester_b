  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiUdp.h>
  #include <ESP8266HTTPClient.h>
//נתונים לאן התחבר -------------------------------------------------------------------------------------
  const char* ssid = "Kinneret College";
  const char* pswd = "";
  
  WiFiClient client;
  int server_port = 80;//http

//מתחבר רק בשלב זה -------------------------------------------------------------------------------------

 
void wifiClient_Setup() {
      Serial.println("wifiSetup");
      //WiFi.begin(ssid, pswd);במידה ויש סיסמה
      WiFi.begin(ssid);
      //בודק האם באמת התחברנו 
        while (WiFi.status() != WL_CONNECTED) {
            Serial.println("trying ...");
            delay(100);
        }
        Serial.println("Connected to network");
}

    //פונה לשרת 

int GetData() {
      int ret = -1;
      HTTPClient http;
      String dataURL = "http://api.kits4.me/GEN/api.php?";
      dataURL += "ACT=GET&DEV=1121&CH=1";
      http.begin(client, dataURL);//תשתמש בקליינט HTTP ותשלח לו את ה URL ששלחנו
      int httpCode = http.GET();
      Serial.println(httpCode);
      if (httpCode == HTTP_CODE_OK) {
          Serial.print("HTTP response code ");
          Serial.println(httpCode);
          String Res = http.getString();
          Serial.println(Res);
          ret = Res.toInt();
      }
      http.end();//סגירת פניה לשרת 
  
  
      return ret;
  }
  //לשנות לשליחה לשרת משהו אחר 
  void sendToServerLockDor(){
    HTTPClient http;
      String dataURL = "http://api.kits4.me/GEN/api.php?";
      dataURL += "ACT=GET&DEV=1121&CH=1&VAL=0";
      http.begin(client, dataURL);//תשתמש בקליינט HTTP ותשלח לו את ה URL ששלחנו
      http.end();//סגירת פניה לשרת 
  }
  
  void sendToServer(unsigned long duration) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://yourserver.com/update");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "duration=" + String(duration);
    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.println("Error on sending POST");
    }
    http.end();
  }
}