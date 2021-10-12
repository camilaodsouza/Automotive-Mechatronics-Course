int PotPin = A0; 
int FETPin = 11;
int PotVal = 0;
int PotValMap = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(FETPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  PotVal = analogRead(PotPin);
  PotValMap = map(PotVal, 0, 1023, 0, 255);
  analogWrite(FETPin, PotValMap);
}
