// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 60;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(5);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(5);
  }
}