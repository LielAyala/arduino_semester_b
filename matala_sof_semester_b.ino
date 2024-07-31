// פינים
#define buttonPin D3;
#define rgbPinR D5;
#define rgbPinG D6;
#define rgbPinB D7;
#define modePin D2;


// משתנים
unsigned long buttonPressTime;
unsigned long shortestPressTime = ULONG_MAX;
bool buttonPressed = false;
bool performanceMode = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(rgbPinR, OUTPUT);
  pinMode(rgbPinG, OUTPUT);
  pinMode(rgbPinB, OUTPUT);
  pinMode(modePin, INPUT);

  Serial.begin(115200);
 
}

void loop() {
  if (digitalRead(modePin) == LOW) {
    performanceMode = true;
    startPerformanceMode();
  } else {
    performanceMode = false;
  }

  if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = true;
    buttonPressTime = millis();
  } else if (digitalRead(buttonPin) == LOW && buttonPressed) {
    unsigned long pressDuration = millis() - buttonPressTime;
    buttonPressed = false;
    if (pressDuration < shortestPressTime) {
      shortestPressTime = pressDuration;
      // שלח לשרת ועדכן
      sendToServer(pressDuration);
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


//לבנות קוד של הצגת ביצועים 
void startPerformanceMode() {
  // קוד למצב הצגת ביצועים
}
