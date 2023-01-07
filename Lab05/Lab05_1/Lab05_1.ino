#define Button_Pin   35
#define LED1_Pin     22
#define LED2_Pin     23
 
void IRAM_ATTR IO_INT_ISR()
{
  // Toggle The LED
  digitalWrite(LED1_Pin, !digitalRead(LED1_Pin));
}
 
void setup()
{
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  attachInterrupt(Button_Pin, IO_INT_ISR, RISING); // interrupt on rising edge
}
 
void loop()
{
  //  without IO interrupt
   digitalWrite(LED2_Pin,HIGH);
   delay(1000);
   digitalWrite(LED2_Pin,LOW);
   delay(1000);
  //  //toggle
  //  digitalWrite(LED1_Pin,digitalRead(!LED1_Pin));
}