const int redLED = 12;
char BTV;

void setup() {
  pinMode(redLED, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    BTV = Serial.read();
    if (BTV=='h') {
      digitalWrite(12,HIGH);
      delay(250);
      digitalWrite(12,LOW);
      delay(250);
    }
    else {
      digitalWrite(12,HIGH);
      delay(500);
      digitalWrite(12,LOW);
      delay(500);
    }
  }
}