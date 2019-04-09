char BTV;
char lastValue;

void setup() {
 Serial.begin(9600);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(12,OUTPUT);
}

void loop() {
  if(Serial.available())
  {
    BTV = Serial.read();
  }
  
  if (BTV == 'd')
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
       
  }
   if (BTV == 'e')
  {
    //digitalWrite(6, HIGH);
    //digitalWrite(7, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
  }
  
  if (BTV == 'f') {
    digitalWrite(6,HIGH);
    lastValue=BTV;
  }
  
 if (BTV == 'g') {
    digitalWrite(7, HIGH);
    lastValue=BTV;
  }
  
  if (BTV == 'h')
  {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    lastValue=BTV; 
  }
  //delay(100);
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