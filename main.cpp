#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define PIN_LED_RED 12
#define PIN_BT_CONNECT 5
#define PIN_MOTOR_LEFT 6
#define PIN_MOTOR_RIGHT 7
#define PIN_MOTOR_LEFT_BACK 10
#define PIN_MOTOR_RIGHT_BACK 11
#define PIN_CLOCK 9
#define PIN_DATA 8
#define PIN_BUZZER 4
#define STACK_SIZE 200

const int c = 2092;
const int d = 2348;
const int e = 2636;
const int f = 2792;
const int g = 3136;
const int gS = 3320;
const int a = 3520;
//const int aS = 455;
const int b = 3728;
const int cH = 4184;
//const int cSH = 554;
//const int dH = 587;
//const int dSH = 622;
const int eH = 5272;
const int fH = 5584;
//const int fSH = 740;
//const int gH = 784;
//const int gSH = 830;
//const int aH = 880;

int counter;
int played = 0;
int i = 0;
char blueToothValue = 'h';
char last_value;

void tMotorControl(void*p) {
	for(;;){
		if (blueToothValue == 'd') {
			//forward
		    digitalWrite(PIN_MOTOR_LEFT, HIGH);
		    digitalWrite(PIN_MOTOR_RIGHT, HIGH);
		    //digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
		    //digitalWrite(PIN_MOTOR_RIGHT_BACK,LOW);
		}
		if (blueToothValue == 'e') {
			//backward
			//digitalWrite(PIN_MOTOR_LEFT,LOW);
			//digitalWrite(PIN_MOTOR_RIGHT,LOW);
		    digitalWrite(PIN_MOTOR_LEFT_BACK, HIGH);
		    digitalWrite(PIN_MOTOR_RIGHT_BACK, HIGH);
		}
		if (blueToothValue == 'f') {
			//turn left
		    digitalWrite(PIN_MOTOR_LEFT,HIGH);
		    //digitalWrite(PIN_MOTOR_RIGHT,LOW);
		    //digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
		    //digitalWrite(PIN_MOTOR_RIGHT_BACK,LOW);
		}
		if (blueToothValue == 'g') {
			//turn right
			//digitalWrite(PIN_MOTOR_LEFT,LOW);
		    digitalWrite(PIN_MOTOR_RIGHT,HIGH);
		    //digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
		    //digitalWrite(PIN_MOTOR_RIGHT_BACK,LOW);
		}
		if (blueToothValue == 'h') {
			//release button
		    digitalWrite(PIN_MOTOR_RIGHT,LOW);
		    digitalWrite(PIN_MOTOR_LEFT, LOW);
		    digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
		    digitalWrite(PIN_MOTOR_RIGHT_BACK,LOW);
		  }
	}
}

void tREDLED(void*p) {
	for(;;) {
		if (blueToothValue=='h' || blueToothValue=='a') {
			if(blueToothValue=='a')digitalWrite(PIN_BT_CONNECT,HIGH);
		    digitalWrite(PIN_LED_RED,HIGH);
		    delay(250);
		    if(blueToothValue=='a')digitalWrite(PIN_BT_CONNECT,LOW);
		    digitalWrite(PIN_LED_RED,LOW);
		    delay(250);
		}
		else {
			digitalWrite(PIN_BT_CONNECT,LOW);
		    digitalWrite(PIN_LED_RED,HIGH);
		    delay(500);
		    digitalWrite(PIN_LED_RED,LOW);
		    delay(500);
		}
	}
}

void tGREENLED(void*p) {
	for(;;) {
		shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B11111111);
		if(blueToothValue=='h'|| blueToothValue=='a'|| blueToothValue=='b') {
			shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B11111111);
		}
		else {
			for(int i=0;i<8;i++) {
				shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B00000001 << i);
				delay(10);
			}
			for(int i=0;i<8;i++) {
				shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B10000000 >>i);
				delay(10);
			}
		}
	}
}

void tSerial(void*p) {
	for(;;) {
		if(Serial.available()) {
			blueToothValue = Serial.read();
		}
	}
}

void beep(int note, int duration)
{
	tone(PIN_BUZZER, note, duration);
    delay(duration);
    noTone(PIN_BUZZER);
    delay(25);
    counter++;
}

void scotlandTheBrave()
{
  beep(c, 1000);
  beep(c, 750);
  beep(d, 250);
  beep(e, 500);
  beep(c, 500);
  beep(e, 500);
  beep(g, 500);

  beep(cH, 1000);
  beep(cH, 750);
  beep(cH, 250);
  beep(cH, 500);
  beep(g, 500);
  beep(e, 500);
  beep(c, 500);

  beep(f, 1000);
  beep(a, 750);
  beep(f, 250);
  beep(e, 500);
  beep(g, 500);
  beep(e, 500);
  beep(c, 500);

  beep(d, 1000);
  beep(g, 750);
  beep(a, 250);
  beep(g, 500);
  beep(f, 500);
  beep(d, 500);
  beep(c, 500);

}
void babyShark()
{
		if (i==0){
		tone(PIN_BUZZER,d,1000);
		delay(250);
		tone(PIN_BUZZER,e,1000);
		delay(250);
		}
	//for(int i=0;i<3;i++){
		if (i != 0){
			delay(125);
		    tone(PIN_BUZZER,d,1000);
		    delay(125);
		    tone(PIN_BUZZER,e,1000);
		    delay(125);
		}
		tone(PIN_BUZZER,g,100);
		delay(125);
		tone(PIN_BUZZER,g,100);
		delay(125);
		tone(PIN_BUZZER,g,100);
		delay(125);
		tone(PIN_BUZZER,g,100);
		delay(63);
		tone(PIN_BUZZER,g,100);
		delay(125);
		tone(PIN_BUZZER,g,100);
		delay(63);
		tone(PIN_BUZZER,g,100);
	//}
		if (i == 2 ){
		delay(150);
		tone(PIN_BUZZER,g,100);
		delay(150);
		tone(PIN_BUZZER,g,100);
		delay(150);
		tone(PIN_BUZZER,5929,100);
		delay(250);
		delay(500);
		i = 0;
		} else i++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}

void tAudio(void*p) {
	for(;;){
		if (blueToothValue=='a'){
			firstSection();
		}
		if (blueToothValue=='b'){
			scotlandTheBrave();
			delay(250);
		}
		else if (blueToothValue>='d' && blueToothValue <= 'h' ){

			babyShark();
			delay(250);
		}
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(PIN_LED_RED,OUTPUT);
	pinMode(PIN_MOTOR_LEFT,OUTPUT);
	pinMode(PIN_MOTOR_RIGHT,OUTPUT);
	pinMode(PIN_MOTOR_LEFT_BACK,OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_BACK,OUTPUT);
	pinMode(PIN_BT_CONNECT,OUTPUT);
	pinMode(PIN_CLOCK,OUTPUT);
	pinMode(PIN_DATA,OUTPUT);
	pinMode(PIN_BUZZER,OUTPUT);
}

void loop() {
	xTaskCreate(tMotorControl, "MotorControl", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tREDLED, "LED", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tGREENLED, "LED", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tAudio, "Audio", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tSerial, "Serial", STACK_SIZE, NULL, 3, NULL);
	vTaskStartScheduler();
}
