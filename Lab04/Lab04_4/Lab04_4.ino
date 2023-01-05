#include "RTClib.h"
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

#define rtcAddress 0x68

Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(rtcAddress);
uint8_t buffer[32];

int second,minute,hour,year,month,date;

String strDate;
String strTime;

void printDate();
void printTime();

void setup() {
  Serial.begin(9600);

  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);

  lcd.begin();
  lcd.backlight();
}

void loop() {
  buffer[0] = 0x00;  // we'll reuse the same buffer
  i2c_dev.write_then_read(buffer, 1, buffer, 8, false);
  second = ((buffer[0]>>4) & 0b111)*10 + (buffer[0] & 0b1111); // parentheses over & operator is necessary!
  minute = ((buffer[1]>>4) & 0b111)*10 + (buffer[1] & 0b1111);
  hour = ((buffer[2]>>4) & 0b11)*10 + (buffer[2] & 0b1111);
  date  = ((buffer[4]>>4) & 0b11)*10 + (buffer[4] & 0b1111);
  month = ((buffer[5]>>4) & 0b1)*10 + (buffer[5] & 0b1111);
  year = ((buffer[6]>>4) & 0b1111)*10 + (buffer[6] & 0b1111) + 2000;

  Serial.print(buffer[6], BIN);
  Serial.print('/');
  Serial.print(buffer[5], BIN);
  Serial.print('/');
  Serial.println(buffer[4], BIN);

  Serial.print(buffer[2], BIN);
  Serial.print(':');
  Serial.print(buffer[1], BIN);
  Serial.print(':');
  Serial.println(buffer[0], BIN);

  Serial.print(year, DEC);
  Serial.print('/');
  Serial.print(month, DEC);
  Serial.print('/');
  Serial.println(date, DEC);

  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.println(second, DEC);

  
  lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
  printDate();
  lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  printTime();

  delay(100);
}

void printDate() {
  String slash = String("/");
  String strYear = String(year);
  String strMonth = String(month > 10 ? "" : "0") + String(month);
  String strDate = String(date > 10 ? "" : "0") + String(date);

  strDate = strYear + slash + strMonth + slash + strDate;
  lcd.print(strDate.c_str());
}

void printTime() {
  String colon = String(":");
  String strHour = String(hour > 10 ? "" : "0") + String(hour);
  String strMinute = String(minute > 10 ? "" : "0") +  String(minute);
  String strSecond = String(second > 10 ? "" : "0") +  String(second);

  strTime = strHour + colon + strMinute + colon + strSecond;
  lcd.print(strTime.c_str());
}