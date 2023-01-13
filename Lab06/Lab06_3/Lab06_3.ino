#define BTN 35

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
const int LED = 16;
const int servoPin = 18;
int pos = 0;

const int freq = 50;
const int servoChannel = 0;
const int resolution = 8;

bool prevState = false;
bool prevLEDState = false;

void write(double ang){
  int dutyCycle = (ang/180)*255;
  ledcWrite(servoChannel, dutyCycle);  
}

portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR IO_INT_ISR()
{
  portENTER_CRITICAL(&synch);
  // Toggle The LED

  if(digitalRead(LED) && !digitalRead(BTN)){
    digitalWrite(LED, LOW);
    write(10);
    delay(10);
    Serial.println("END TURN");
  }

  portEXIT_CRITICAL(&synch);
}

void setup() {
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(servoPin, servoChannel);

  // configure LED PWM functionalitites
  ledcSetup(servoChannel, freq, resolution);

  Serial.begin(9600);
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);
  attachInterrupt(BTN, IO_INT_ISR, FALLING);
}

void loop() {
  if(prevState && !digitalRead(BTN) && !prevLEDState){
    prevState = false;
  
    Serial.println("BEGIN TURN");

digitalWrite(LED, HIGH);
    for (pos = 10; pos <= 168; pos += 1) {
      write(pos);
      delay(10);
    }

  } else { prevState = digitalRead(BTN); }
  prevLEDState = digitalRead(LED);

  if(!digitalRead(LED))
    write(10);

  delay(10);
}