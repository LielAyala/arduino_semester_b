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
