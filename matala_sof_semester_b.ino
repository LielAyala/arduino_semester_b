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
void BtnAndLedRGB_setup() {
  pinMode(PinBlue, OUTPUT);
  pinMode(PinGreen, OUTPUT);
  pinMode(PinRed, OUTPUT);
  pinMode(Btn_R, INPUT_PULLUP);
  Serial.begin(9600);
  TurnOffLED(); // מכבה את ה-LED
  
}
void TurnOffLED() {
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 0);
  analogWrite(PinBlue, 0);
}
