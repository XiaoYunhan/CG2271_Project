#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define PIN_LED_RED 12
#define PIN_MOTOR_LEFT 6
#define PIN_MOTOR_RIGHT 7
#define PIN_MOTOR_LEFT_BACK 10
#define PIN_MOTOR_LEFT_BACK 11
#define PIN_CLOCK 9
#define PIN_DATA 8
#define STACK_SIZE 200

char blueToothValue;

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
		    digitalWrite(PIN_MOTOR_LEFT_BACK, HIGH);
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
		    digitalWrite(PIN_MOTOR_LEFT_BACK,LOW);
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
        	shiftOut(dataPin,clockPin,MSBFIRST,B00000001 << i);
    		delay(125);
  		}
  		for(int i=0;i<8;i++) {
    		shiftOut(dataPin,clockPin,MSBFIRST,B10000000 >>i);
    		delay(125);
  		}
	}
}

void tAudio(void*p) {
	for(;;) {

	}

}

void tSerial(void*p) {
	for(;;) {
		if(Serial.available()) blueToothValue = Serial.read();
	}
}

void setup() {
	pinMode(PIN_LED_RED,OUTPUT);
	pinMode(PIN_MOTOR_LEFT,OUTPUT);
	pinMode(PIN_MOTOR_RIGHT,OUTPUT);
	pinMode(PIN_MOTOR_LEFT_BACK,OUTPUT);
	pinMode(PIN_MOTOR_LEFT_BACK,OUTPUT);
	pinMode(PIN_CLOCK,OUTPUT);
	pinMode(PIN_DATA,OUTPUT);
}

void loop() {
	xTaskCreate(tMotorControl, "MotorControl", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tREDLED, "LED", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tGREENLED, "LED", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tAudio, "Audio", STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(tSerial, "Serial", STACK_SIZE, NULL, 4, NULL);
	vTaskStartScheduler();
}
