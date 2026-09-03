#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

#define GREEN_LED     A0
#define RED_LED       A1

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

byte allowedUID[4] = {0xD3, 0xAA, 0xB2, 0x14};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  lcd.clear();

  if (compareUID(rfid.uid.uidByte, allowedUID, rfid.uid.size)) {
    lcd.print("Access Granted");
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

  } else {
    lcd.print("Access Denied");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  delay(1500);
  lcd.clear();
  lcd.print("Scan your card");

  rfid.PICC_HaltA();
}

bool compareUID(byte *buffer, byte *uid, byte size) {
  if (size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (buffer[i] != uid[i]) return false;
  }
  return true;
}
