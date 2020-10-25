// Partially based on https://makersportal.com/blog/2019/5/27/arduino-interrupts-with-pir-motion-detector

volatile int state = LOW;
const int interrupt_pin = 2;
int movement = LOW;
const int photoresistor = A0;
const int led = 6;
const int play = 12;
int lum = 1;
int brightness = 81;
int treshold = 240;    // Level of light below which the eyes will trigger: 20 is a good default
int dur = 2;  // Duration of flicker

void setup() {
  pinMode(led, OUTPUT);
  pinMode(play, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),detection,RISING);
  delay(3000);
  digitalWrite(led, LOW);
}


/*
void loop() {
  digitalWrite(led, LOW);
  lum = analogRead(photoresistor);
//  Serial.print("Brightness: ");
//  Serial.println(lum);
  movement = digitalRead(pir);
  if (lum < treshold && movement == 1){
    Serial.println("Gotcha!");
    digitalWrite(led, HIGH);
    digitalWrite(play, HIGH);
    delay(150);
    digitalWrite(play,LOW);
    for(int i=0; i<90; i++){
      int brightness = random(81);
      if (brightness > 79){
        digitalWrite(led, HIGH);
        delay(40);
      } else if (brightness < 20){
        digitalWrite(led,0);
        Serial.println("LOW");
        delay(40);
      } else {
        analogWrite(led, brightness);
        Serial.println(brightness);
        delay(40);
      }
    }
  digitalWrite(led, LOW);
  delay(5000);
  }
}
*/


void loop() {
  if (state == HIGH){
    lum = analogRead(photoresistor);
    Serial.print("Lum: ");
    Serial.println(lum);
    if (lum < treshold){
      Serial.println("Gotcha!");
      flicker();
      }
    digitalWrite(led, LOW);
    }
    
  
  state = LOW;
}


void flicker(){
  digitalWrite(play,HIGH);
  digitalWrite(play,LOW);
  for(int i=0; i<90; i++){
    int brightness = random(81);
    if (brightness > 79){
      digitalWrite(led, HIGH);
      delay(40);
    } else if (brightness < 20){
      digitalWrite(led,0);
      Serial.println("LOW");
      delay(40);
    } else {
      analogWrite(led, brightness);
      Serial.println(brightness);
      delay(40);
    }
  }
}

void detection(){
  state = HIGH;
}
