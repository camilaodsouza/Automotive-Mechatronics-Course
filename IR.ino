int pinLed = 11; 
int pinReceiver = A0;
int receiver = 0;
int mapedReceiver = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinLed, OUTPUT);
  pinMode(pinReceiver, INPUT);
  Serial.begin(9600); 
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinLed, HIGH); 
  receiver = constrain(map(analogRead(pinReceiver),2000, 300, 255, 0), 0 ,220);
  Serial.println(receiver);
  delay(100);
}
