// Partially based on https://makersportal.com/blog/2019/5/27/arduino-interrupts-with-pir-motion-detector


const int led = 6;
volatile int state = LOW;
const int interrupt_pin = 2;
int movement = LOW;
const int photoresistor = A0;
int lum = 1;
int dur = 3;  // Duration of flicker
int treshold = 20;    // Level of darkness below which the eyes will trigger 


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),detection,RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == HIGH){
    lum = analogRead(photoresistor);
    Serial.print("Lum: ");
    Serial.println(lum);
    if (lum < treshold){
      Serial.println("Gotcha!");
      flicker(dur);
      }
    digitalWrite(led, LOW);
    }
    
  
  state = LOW;
}


void flicker(int s){
  int dur = s*1000;
  int t = millis();
  digitalWrite(led,HIGH);
  delay(150);
  while (millis()<(t+dur)){
    int brightness = random(81);
    if (brightness > 79){
      digitalWrite(led,HIGH);
   //   Serial.println("HIGH");
      delay(80);
    } else if (brightness < 20){
      digitalWrite(led,LOW);
   //   Serial.println("LOW");
      delay(40);
    } else {
      analogWrite(led, brightness);
   //   Serial.println(brightness);
      delay(10);
    }
  }
}


void detection(){
  state = HIGH;
}
