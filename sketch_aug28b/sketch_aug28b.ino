#include <Alash_DS1302.h>
#include <SevSeg.h>

#define DS1302_CLK_PIN A0
#define DS1302_IO_PIN  A1
#define DS1302_CE_PIN  A5 

Alash_DS1302 rtc = Alash_DS1302(DS1302_CLK_PIN, DS1302_IO_PIN, DS1302_CE_PIN);
SevSeg sevseg;

void setup() {
  Serial.begin(9600);

  while (!rtc.begin()) {
    Serial.println(F("RTC not found"));
    delay(1000);
  }

  if (!rtc.isRunning()) {
    rtc.clockEnable(true);
    rtc.setDateTime(14, 30, 0, 28, 8, 2026, 5); 
  }

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0;
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  uint8_t hour, minute, second;
  if (rtc.getTime(&hour, &minute, &second)) {
    int timeValue = hour * 100 + minute;   
    sevseg.setNumber(timeValue, 2);        
  }
  sevseg.refreshDisplay();
}
