
const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int VRxPin = A0;
const int VRyPin = A1;
const int SWPIN = 2;

int VRx;
int VRy;
int SW;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(VRxPin, INPUT);
  pinMode(VRyPin, INPUT);
  pinMode(SWPIN, INPUT);

}

void writeToShiftRegister(byte data) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, data);

  digitalWrite(latchPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  byte num = 0b00000000;

  VRx = analogRead(VRxPin);
  VRy = analogRead(VRyPin);
  SW = digitalRead(SWPIN);

  if (VRx < 400) {
    num = 0b10000000;
  }else if (VRx > 600) {
    num = 0b00100000;
  }else {
    num = 0b01000000;
  }

  writeToShiftRegister(num);
  
  Serial.print("X: ");
  Serial.print(VRx);
  Serial.print(". Y: ");
  Serial.print(VRy);
  Serial.print(". SW: ");
  Serial.println(SW);

  delay(200);
}
