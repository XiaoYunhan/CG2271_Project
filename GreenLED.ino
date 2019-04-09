const int clockPin = 9;
const int dataPin = 8;

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for(int i=0;i<8;i++) {
    shiftOut(dataPin,clockPin,MSBFIRST,B00000001 << i);
    delay(125);
  }
  for(int i=0;i<8;i++) {
    shiftOut(dataPin,clockPin,MSBFIRST,B10000000 >>i);
    delay(125);
  }
}