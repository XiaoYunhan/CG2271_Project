#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define PIN_LED_RED 12
#define PIN_MOTOR_LEFT 6
#define PIN_MOTOR_RIGHT 7
#define PIN_MOTOR_LEFT_BACK 10
#define PIN_MOTOR_RIGHT_BACK 11
#define PIN_CLOCK 9
#define PIN_DATA 8
#define PIN_BUZZER 4
#define STACK_SIZE 200

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

int counter;

char blueToothValue;
char dmb;

void myDelay(int ms) {
	for(int i=0;i<ms;i++) {
		delayMicroseconds(1000);
	}
}

void tMotorControl(void*p) {
	for(;;){
		if (blueToothValue == 'd') {
		    digitalWrite(PIN_MOTOR_LEFT, HIGH);
		    digitalWrite(PIN_MOTOR_RIGHT, HIGH);
		}
		if (blueToothValue == 'e') {
		    digitalWrite(PIN_MOTOR_LEFT_BACK, HIGH);
		    digitalWrite(PIN_MOTOR_RIGHT_BACK, HIGH);
		}
		if (blueToothValue == 'f') {
		    digitalWrite(PIN_MOTOR_LEFT,HIGH);
		}
		if (blueToothValue == 'g') {
		    digitalWrite(PIN_MOTOR_RIGHT, HIGH);
		}
		if (blueToothValue == 'h') {
		    digitalWrite(PIN_MOTOR_LEFT, LOW);
		    digitalWrite(PIN_MOTOR_RIGHT, LOW);
		    digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
		    digitalWrite(PIN_MOTOR_RIGHT_BACK,LOW);
		  }
	}
}

void tREDLED(void*p) {
	for(;;) {
		if (blueToothValue=='h') {
		    digitalWrite(PIN_LED_RED,HIGH);
		    delay(250);
		    digitalWrite(PIN_LED_RED,LOW);
		    delay(250);
		}
		else {
		    digitalWrite(PIN_LED_RED,HIGH);
		    delay(500);
		    digitalWrite(PIN_LED_RED,LOW);
		    delay(500);
		}
	}
}

void tGREENLED(void*p) {
	for(;;) {
		for(int i=0;i<8;i++) {
        	shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B00000001 << i);
    		delay(125);
  		}
  		for(int i=0;i<8;i++) {
    		shiftOut(PIN_DATA,PIN_CLOCK,MSBFIRST,B10000000 >>i);
    		delay(125);
  		}
	}
}

void tSerial(void*p) {
	for(;;) {
		if(Serial.available())blueToothValue = Serial.read();
		//if(!Serial.read()) digitalWrite(PIN_MOTOR_RIGHT,HIGH);
	}
}

void beep(int note, int duration)
{
	tone(PIN_BUZZER, note, duration);
    delay(duration);
    noTone(PIN_BUZZER);
    delay(50);
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
  beep(d, 300);
  beep(e, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);

  delay(500);

  beep(d, 300);
  beep(e, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);

  delay(500);

  beep(d, 300);
  beep(e, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);
  beep(g, 200);

  delay(500);
  beep(g, 300);
  beep(g, 200);
  beep(370, 200);
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

void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);
  beep(cSH, 175);
  beep(cH, 125);
  beep(b, 125);
  beep(cH, 250);

  delay(350);
}

void tAudio(void*p) {
	for(;;){
		scotlandTheBrave();
		delay(250);
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(PIN_LED_RED,OUTPUT);
	pinMode(PIN_MOTOR_LEFT,OUTPUT);
	pinMode(PIN_MOTOR_RIGHT,OUTPUT);
	pinMode(PIN_MOTOR_LEFT_BACK,OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_BACK,OUTPUT);
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
