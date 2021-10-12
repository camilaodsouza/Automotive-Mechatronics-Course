const int AnalogIn_Pin0 = A0;
const int AnalogIn_Pin1 = A1;
const int PwmOut_PIN = 11;
float AnalogIn_Val0 = 0;
float AnalogIn_Val1 = 0;
int PwmOut_Val = 0;
float Error = 0;
float ErrorInteg = 0;
float Control = 0;
float ControlFilt = 0;
float Kp = 0.4;//Original = 0.2
float Pole = -10;
float Ki = - Pole*Kp;
float deltaT = 0.01;
int deltaT_ms = (int)deltaT*1000;
float per = 1; //0.97
char c;

void setup() {
  pinMode(PwmOut_PIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
 if(Serial.available()){
    c = Serial.read();
    if(c == 'R'){
       analogWrite(PwmOut_PIN, 0);
       ControlFilt = 0;
       delay(70);
    }
 }
  //SETPOINT
    AnalogIn_Val0 = (float)map(analogRead(AnalogIn_Pin0),0,1023, 700, 800);
  //PV
    AnalogIn_Val1 = analogRead(AnalogIn_Pin1);
    
  //Control Algorithm
    
    Error = (AnalogIn_Val0 - AnalogIn_Val1);
      ErrorInteg = ErrorInteg + Error*deltaT;
        ControlFilt = Kp*Error + Ki*ErrorInteg;

    //Mapeando PWM 0 -> 255
    // MV
        PwmOut_Val = constrain(map((int)ControlFilt,0,1023,0,255),0,220);
      analogWrite(PwmOut_PIN, PwmOut_Val);
   // Sending Through the Serial   
    Serial.print(AnalogIn_Val0 - 700);//SP
      Serial.print('\t');
        Serial.print(AnalogIn_Val1-700);//PV
          Serial.print('\t');
            Serial.println(PwmOut_Val/(2.55));//MV
    delay(deltaT_ms);
}
