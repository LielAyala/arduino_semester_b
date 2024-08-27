// פינים
#define buttonPin D3
#define rgbPinR D5
#define rgbPinG D6
#define rgbPinB D7
#define modePin D2

// משתנים
unsigned long buttonPressTime;
unsigned long shortestPressTime = ULONG_MAX;
bool buttonPressed = false;
bool performanceMode = false;

// הצהרה על הפונקציות שמגיעות מהקובץ של ה-WiFi
void wifiClient_Setup();
bool sendToServer(unsigned long duration);

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(rgbPinR, OUTPUT);
  pinMode(rgbPinG, OUTPUT);
  pinMode(rgbPinB, OUTPUT);
  pinMode(modePin, INPUT);

  Serial.begin(115200);

  // חיבור לרשת WiFi
  wifiClient_Setup();
}

void loop() {
  // בדיקה אם פין המוד מחובר לאדמה
  if (digitalRead(modePin) == LOW) {
    performanceMode = true;
    startPerformanceMode();
  } else {
    performanceMode = false;
  }

  // קריאה לפונקציה שמודדת את משך הלחיצה
  Measuring_click_duration();
}

void Measuring_click_duration() {
  // בדיקה אם הכפתור לחוץ והמדידה מתחילה
  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;
    buttonPressTime = millis(); // שמירת הזמן שהכפתור התחיל להלחץ
  } 
  // בדיקה אם הכפתור שוחרר והמדידה מסתיימת
  else if (digitalRead(buttonPin) == LOW && buttonPressed) {
    unsigned long pressDuration = millis() - buttonPressTime; // חישוב משך הלחיצה
    buttonPressed = false;
    if (sendToServer(pressDuration)) {
      shortestPressTime = pressDuration;
      setRGBColor(64, 224, 208); // תכלת טורקיז
    } else {
      setRGBColor(255, 165, 0); // כתום
    }
  }
}

void setRGBColor(int r, int g, int b) {
  analogWrite(rgbPinR, r);
  analogWrite(rgbPinG, g);
  analogWrite(rgbPinB, b);
}

void startPerformanceMode() {
  // קוד למצב הצגת ביצועים
}
