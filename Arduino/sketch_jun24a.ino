// Variables
unsigned long startTime = 0;
unsigned long previousMillis = 0;
double light = 0;
int cnt = 0;
int stage = 1;

// Define values from mongo
String response;
int heatingTime;
int lightLevelTime;
int activationTime;
int pauseTime;

// Define pins
#define LDR A0
#define PinRelay D5
#define RedLed D6

void setup() {
  Serial.begin(9600);
  pinMode(PinRelay, OUTPUT);
  pinMode(RedLed, OUTPUT);
  wifi_Setup();
  fetchTimeData();
}

void loop() {
  if (heatingTime >= 2 && lightLevelTime >= 2 && activationTime >= 2 && pauseTime >= 2) {
    switch (stage) {
      case 1:
        heat();
        break;
      case 2:
        lig();
        break;
      case 3:
        active();
        break;
      case 4:
        Pause();
        break;
      default:
        break;
    }
  } else {
    Serial.println("Put Each Stage Timing Equal Or Above 2");
    fetchTimeData();
  }
}




void heat() {
  unsigned long currentMillis = millis();
  if (startTime == 0) {
    startTime = currentMillis;
  }

  if (currentMillis - startTime <= (heatingTime * 1000)) {
    digitalWrite(RedLed, HIGH);
    digitalWrite(PinRelay, HIGH);
  } else {
    startTime = 0;
    digitalWrite(RedLed, LOW);
    digitalWrite(PinRelay, LOW);
    Serial.println("Moving to stage 2");
    Serial.println("Inside the light level");
    stage = 2;
  }
}

void lig() {
  unsigned long currentMillis = millis();
  if (startTime == 0) {
    startTime = currentMillis;
  }

  if (currentMillis - startTime <= (lightLevelTime * 1000)) {
    if (currentMillis - previousMillis >= 1000) {
      light += map(analogRead(LDR), 0, 1023, 0, 255);
      cnt++;
      Serial.println(light);
      Serial.println(cnt);
      previousMillis = currentMillis;
    }
  } else {
    startTime = 0;
    light = light / cnt;
    Serial.println("Moving to stage 3");
    Serial.println("Inside the activation");
    stage = 3;
  }
}

void active() {
  unsigned long currentMillis = millis();
  if (startTime == 0) {
    startTime = currentMillis;
  }

  if (currentMillis - startTime <= (activationTime * 1000)) {
    analogWrite(RedLed, light);
  } else {
    analogWrite(RedLed, LOW);
    startTime = 0;
    Serial.println("Moving to stage 4");
    Serial.println("Inside the pause");
    stage = 4;
  }
}

void Pause() {
  unsigned long currentMillis = millis();
  if (startTime == 0) {
    startTime = currentMillis;
  }

  if (currentMillis - startTime <= (pauseTime * 1000)) {
    Serial.println("Waiting In Pause");
  } else {
    Serial.println("Moving back to stage 1");
    Serial.println("Inside the heating");
    light = 0;
    cnt = 0;
    startTime = 0;
    fetchTimeData();
    stage = 1;
  }
}
