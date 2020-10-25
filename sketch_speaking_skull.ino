const int led = 6;
volatile int state = LOW;
const int pir = 2;
int movement = LOW;
const int photoresistor = A0;
const int play = 12;
int lum = 1024;
int brightness = 81;
int treshold = 160;    // Level of light below which the eyes will trigger: 20 is a good default


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  pinMode(pir, INPUT);
  delay(3000);
  Serial.begin(9600);
  pinMode(play, OUTPUT);
}

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
