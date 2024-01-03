#define en_a 2
#define en_b 3

unsigned long currentMillis;
unsigned long prevMillis;
volatile long encoder0Pos;
float encoder0Prev;
float encoder0Diff;
float speed_act_left;
float speed_rpm;
float v1Filt;
float v1Prev;

void setup() {
  Serial.begin(115200);
  pinMode(en_a, INPUT_PULLUP);
  pinMode(en_b, INPUT_PULLUP);
  Serial.println("basic encoder test");

  attachInterrupt(digitalPinToInterrupt(en_a), change_left_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(en_b), change_left_b, CHANGE);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - prevMillis >= 10) {
    prevMillis = currentMillis;
    encoder0Diff = encoder0Pos - encoder0Prev;
    speed_act_left = encoder0Diff / 10 * 1000;
    speed_rpm = speed_act_left / 16000 * 60;
    v1Filt = 0.854 * v1Filt + 0.0728 * speed_rpm + 0.0728 * v1Prev;
    v1Prev = speed_rpm;
    encoder0Prev = encoder0Pos;
    Serial.print(encoder0Pos);
    Serial.print(",");
    Serial.print(speed_rpm);
    Serial.print("rpm");
    Serial.print("");
    Serial.print(v1Filt);
    Serial.print("filtered rpm");
    Serial.println();
  }
}

void change_left_a() {
  if (digitalRead(en_a) == HIGH) {
    if (digitalRead(en_b) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    } else {
      encoder0Pos = encoder0Pos - 1;
    }
  } else {
    if (digitalRead(en_b) == HIGH) {
      encoder0Pos = encoder0Pos + 1;
    } else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
}

void change_left_b() {
  if (digitalRead(en_b) == HIGH) {
    if (digitalRead(en_a) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    } else {
      encoder0Pos = encoder0Pos - 1;
    }
  } else {
    if (digitalRead(en_a) == HIGH) {
      encoder0Pos = encoder0Pos + 1;
    } else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
}
