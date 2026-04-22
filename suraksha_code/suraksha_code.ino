#include <SoftwareSerial.h>

SoftwareSerial a9g(8, 9);   

#define SOS_PIN 6
#define LONG_PRESS 1000

char phoneNumber1[] = "+919890384980";   
char smsText[180];
char phoneNumber2[] = "+917276664757";   
char smsText[180];

float lastLat = 0.0;
float lastLon = 0.0;

unsigned long pressStart = 0;
bool sosTriggered = false;

/* ================= SETUP ================= */
void setup() {
  pinMode(SOS_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  a9g.begin(9600);

  delay(4000);

  a9g.println("AT");
  delay(1000);
  a9g.println("ATE0");
  delay(1000);
  a9g.println("AT+CMGF=1");
  delay(1000);
  a9g.println("AT+GPS=1");
  delay(1000);

  Serial.println("SOS Tracker Ready");
}

/* ================= LOOP ================= */
void loop() {
  checkButton();
}

/* ================= BUTTON ================= */
void checkButton() {
  if (digitalRead(SOS_PIN) == LOW) {
    if (pressStart == 0) pressStart = millis();
    else if ((millis() - pressStart) > LONG_PRESS && !sosTriggered) {
      sosTriggered = true;
      triggerSOS();
    }
  } else {
    pressStart = 0;
    sosTriggered = false;
  }
}

/* ================= SOS ================= */
void triggerSOS() {
  Serial.println("SOS ACTIVATED");

  lastLat = 0.0;
  lastLon = 0.0;

  unsigned long start = millis();

  while (millis() - start < 15000) {
    readGPSOnce();
    if (lastLat != 0.0 && lastLon != 0.0) break;
    delay(1000);
  }

  if (lastLat != 0.0 && lastLon != 0.0) {
    char latStr[16], lonStr[16];
dtostrf(lastLat, 0, 6, latStr);
dtostrf(lastLon, 0, 6, lonStr);

snprintf(smsText, sizeof(smsText),
         "SOS ALERT!\nhttps://maps.google.com/?q=%s,%s",
         latStr, lonStr);

  } else {
    snprintf(smsText, sizeof(smsText),
             "SOS ALERT!\nLocation unavailable");
  }

  Serial.print("FINAL SMS: ");
  Serial.println(smsText);

  sendSMS(smsText);
  makeCall();
}

/* ================= GPS ================= */
void readGPSOnce() {
  char buf[220];
  int i = 0;

  while (a9g.available()) a9g.read();
  a9g.println("AT+LOCATION=2");

  unsigned long t = millis();
  while (millis() - t < 8000) {
    while (a9g.available()) {
      char c = a9g.read();
      if (i < sizeof(buf) - 1) buf[i++] = c;
    }
  }
  buf[i] = '\0';

  Serial.println("GPS RAW:");
  Serial.println(buf);

  // Find comma-separated coordinates
  char *comma = strchr(buf, ',');
  if (!comma) return;

  // Backtrack to start of number
  char *start = comma;
  while (start > buf && (*(start - 1) >= '0' && *(start - 1) <= '9' || *(start - 1) == '.'))
    start--;

  lastLat = atof(start);
  lastLon = atof(comma + 1);

  if (lastLat != 0.0 && lastLon != 0.0) {
    Serial.println("GPS SAVED");
  }
}

/* ================= SMS ================= */
void sendSMS(char *msg) {
  a9g.print("AT+CMGS=\"");
  a9g.print(phoneNumber);
  a9g.println("\"");
  delay(1000);
  a9g.print(msg);
  delay(500);
  a9g.write(26);
  delay(5000);
}

/* ================= CALL ================= */
void makeCall() {
  a9g.print("ATD");
  a9g.print(phoneNumber);
  a9g.println(";");
  delay(20000);
  a9g.println("ATH");
}
