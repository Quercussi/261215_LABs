#include <ESP32Servo.h>

#define BTN 35

Servo myservo;
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
const int LED = 16;
const int servoPin = 18;
int pos = 0;

bool prevState = false;
bool prevLEDState = false;

const int freq = 60;
const int ledChannel = 0;
const int resolution = 8;

portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR IO_INT_ISR()
{
  portENTER_CRITICAL(&synch);
  // Toggle The LED

  if(digitalRead(LED) && !digitalRead(BTN)){
    digitalWrite(LED, LOW);
    myservo.write(10);
    delay(20);
    Serial.println("END TURN");
  }

  portEXIT_CRITICAL(&synch);
}

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);
  myservo.attach(servoPin);
  attachInterrupt(BTN, IO_INT_ISR, FALLING);
}

void loop() {
  if(prevState && !digitalRead(BTN) && !prevLEDState){
    prevState = false;
  
    Serial.println("BEGIN TURN");

digitalWrite(LED, HIGH);
    for (pos = 10; pos <= 168; pos += 1) {
      myservo.write(pos);
      delay(20);
    }

  } else { prevState = digitalRead(BTN); }
  prevLEDState = digitalRead(LED);
  delay(10);
}