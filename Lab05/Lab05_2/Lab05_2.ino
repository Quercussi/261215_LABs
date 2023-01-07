#define LED 21
hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.

const int clk_speed = 1000000;
const int notes[] = {0,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976};

void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}

void setup() {
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  timerAlarmWrite(My_timer, duration, true);  // set alarm every 1 sec
  timerAlarmEnable(My_timer);  // enable the alarm
}

void loop() {

}