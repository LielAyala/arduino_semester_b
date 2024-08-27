

// פינים
#define buttonPin D3 // מגדיר את הפין לכפתור
#define rgbPinR D5 // מגדיר את הפין לנורת ה-LED בצבע אדום
#define rgbPinG D6 // מגדיר את הפין לנורת ה-LED בצבע ירוק
#define rgbPinB D7 // מגדיר את הפין לנורת ה-LED בצבע כחול


//פין של מצב (האם מחובר לאדמה או לא )
#define modePin D2 // מגדיר את הפין למצב עבודה (האם מחובר לאדמה או לא)




// משתנים


const int MAX_SIZE=100 ; // הגדרת גודל מקסימלי למערך השומר את זמני הלחיצות


int valFromServer; // משתנה לשמירת הערך מהשרת
unsigned long pressStartTime = 0; // שמירת זמן התחלת הלחיצה
unsigned long LastPress = 0; // שמירת משך הלחיצה האחרונה
int pressDuration = 0; // שמירת משך הלחיצה הנוכחית
bool isButtonPressed = false; //בדיקה האם הכפתור נלחץ
bool isLEDOn = false; //בדיקה האם הלד דולק
unsigned long pressRecords[MAX_SIZE] = {0}; // מערך לשמירת זמני הלחיצות
bool isRecordNew[MAX_SIZE] = {false}; // מערך לבדיקת האם הלחיצה היא שיא חדש
int recordIndex = 0; // אינדקס למעקב אחר מיקום במערך הלחיצות
// משתנה גלובלי לשמירת מצב הפעלה
bool currentMode; // משתנה לשמירת המצב הנוכחי (שרת או לא)
bool flag=true; // דגל לבדיקת האם יש צורך לבצע הגדרות WiFi




void setup() {
  pinMode(SETTING_PIN, INPUT_PULLUP); // מגדיר את הפין כקלט עם התנגדות פנימית למשיכה למעלה
  Serial.begin(9600); // פותח את התקשורת הסדרתית במהירות 9600 bps
 
  BtnAndLedRGB_setup(); // קורא לפונקציה המגדירה את הכפתור ואת נורות ה-LED
  Serial.println("Game Client setup complete."); // הודעה לסדרה שההגדרות הסתיימו
}


void loop() {
  // בדיקה שגרתית של מצב הפין
  currentMode = digitalRead(SETTING_PIN) == LOW; // בדיקה אם הפין מחובר לאדמה, במצב כזה המצב הוא "שרת"
  if(currentMode && flag){
    WifiSetup(); // הגדרת WiFi אם במצב שרת
    flag=false; // הגדרת דגל לכך שההגדרה בוצעה
  }else if(currentMode){
    TurnOffLED(); // כיבוי ה-LED במצב שרת
    WifiServer_loop(); // ניהול לולאת שרת ה-WiFi
  }else{
    BtnAndLedRGB_loop(); //ניהול הכפתור וה-LED במצב עבודה רגיל
  }
}




void BtnAndLedRGB_setup() {
  pinMode(PinBlue, OUTPUT);
  pinMode(PinGreen, OUTPUT);
  pinMode(PinRed, OUTPUT);
  pinMode(Btn_R, INPUT_PULLUP);
  Serial.begin(9600);
  TurnOffLED(); // מכבה את ה-LED
  wifiClient_Setup(); // קורא לפונקציה המגדירה את חיבור ה-WiFi כקליינט
}




void BtnAndLedRGB_loop(){
  int buttonState = digitalRead(Btn_R); // קריאת המצב הנוכחי של הכפתור


  if (buttonState == LOW) {
      if (!isButtonPressed) {
          pressStartTime = millis(); // התחלת מדידת זמן הלחיצה
          isButtonPressed = true; // סימון שהכפתור נלחץ
      }
  } else {
      if (isButtonPressed) {
          LastPress = millis() - pressStartTime; // חישוב משך הלחיצה
          isButtonPressed = false; // סימון שהכפתור שוחרר


          valFromServer = GetData(); // קבלת נתונים מהשרת


          Serial.print("Value from server: ");
          Serial.println(valFromServer); // הדפסת הערך שהתקבל מהשרת


          Serial.print("Press duration: ");
          Serial.print(LastPress);
          Serial.println(" milliseconds"); // הדפסת משך הלחיצה




          bool isNewRecord = (LastPress < valFromServer); // בדיקה אם משך הלחיצה הוא שיא חדש
         
          recordPress(LastPress, isNewRecord);  // שמירת משך הלחיצה והשיא במערך


          if (isNewRecord) {
              Turkiz(); // שינוי צבע ה-LED לכחול-טורקיז אם השיא חדש
              SetNewRecordToServer(LastPress); // שליחת השיא החדש לשרת
          } else {
              Orange(); // שינוי צבע ה-LED לכתום אם השיא לא חדש
          }


          delay(100);
      }
  }
}




void Orange() {
  analogWrite(PinRed, 255);
  analogWrite(PinGreen, 165);
  analogWrite(PinBlue, 0);
}


void Turkiz() {
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 255);
  analogWrite(PinBlue, 255);
}


void TurnOffLED() {
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 0);
  analogWrite(PinBlue, 0);
}




void recordPress(unsigned long duration, bool isNewRecord) {
  pressRecords[recordIndex] = duration; // שמירת משך הלחיצה במערך
  isRecordNew[recordIndex] = isNewRecord; // שמירת האם מדובר בשיא חדש במערך
  recordIndex = (recordIndex + 1) % MAX_SIZE; // מעבר לאינדקס הבא במערך עם מחזוריות
}






