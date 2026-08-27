int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int potentiometerPin = A0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

int scalePotentiometerValue(int x) {
  return map(x, 0, 1023, 0, 8);
}

void loop() {
  // put your main code here, to run repeatedly:

  int pVal = analogRead(potentiometerPin);

  Serial.print("P value is: ");
  Serial.println(pVal);

  int scaledVal = scalePotentiometerValue(pVal);

  Serial.print("Scaled val is: ");
  Serial.println(scaledVal);

  byte num = (1 << scaledVal) - 1;

  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, num);

  digitalWrite(latchPin, HIGH);
}
