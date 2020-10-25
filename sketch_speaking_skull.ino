// Based on https://makersportal.com/blog/2019/5/27/arduino-interrupts-with-pir-motion-detector

#include <LowPower.h>

volatile byte state = LOW;
const int interrupt_pin = 2;
int movement = LOW;
const int photoresistor = A0;
const int led = 6;
const int play = 12;
int lum = 1;
int brightness = 81;
int treshold = 50;    // Level of light below which the eyes will trigger: 20 is quite dark.

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  pinMode(play, OUTPUT);
  digitalWrite(interrupt_pin, HIGH);
 // Serial.begin(9600);
  delay(3000);
  digitalWrite(led, LOW); 
}


void loop() {
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),detection,RISING);
  LowPower.powerDown(SLEEP_FOREVER,ADC_OFF,BOD_OFF); // sleep until interrupt
  detachInterrupt(digitalPinToInterrupt(interrupt_pin)); // remove interrupt
  // the usual wake routine that turns on the LED
  if (state == HIGH){
    lum = analogRead(photoresistor);
 //   Serial.print("Lum: ");
 //   Serial.println(lum);
    if (lum < treshold){
      flicker();
      }
    digitalWrite(led, LOW);
    state = LOW;
  }
}


void flicker(){
  digitalWrite(play,HIGH);
  for(int i=0; i<90; i++){
    int brightness = random(81);
    if (brightness > 79){
      digitalWrite(led, HIGH);
      delay(40);
    } else if (brightness < 20){
      digitalWrite(led,0);
 //     Serial.println("LOW");
      delay(40);
    } else {
      analogWrite(led, brightness);
 //     Serial.println(brightness);
      delay(40);
    }
    
  }
  digitalWrite(play,LOW);
}

void detection(){
 // Serial.println("Gotcha!");
  state = HIGH; 
}
