/*  LightDimmer.ino
 *   Created by Camila Oliveira de Souza
 *   November 2018
*/
int setpoint_PIN = A0;
int photoRead_PIN = A1;// a potentiometer is to be connected to analog pin A0
int PWM_PIN = 11; // digital pin 11 will be used to output PWM
float setpoint_VALUE = 0;
float photoValue = 0;
int PWMValue = 0;
float error = 0;
float errorInt = 0;
float control = 0;
float controlFilt = 0;
float Kp = 1.3;
float pole = -20;
float Ki = - pole*Kp;
float deltaT = 0.01;
float deltaT_ms = (int) deltaT*1000;


void setup() {
  pinMode(PWM_PIN , OUTPUT);  // declare that digital pin as output
  //pinMode(test_PIN, OUTPUT); // Seeing better
  Serial.begin(9600);
}

void loop() {
  //Accquiring Data From Sensors
  //setpoint_VALUE = (float)constrain(analogRead(setpoint_PIN), 400, 800); //Read the setpoint value from the potentiometer
  setpoint_VALUE = (float)map(analogRead(setpoint_PIN), 0, 1023, 600, 800);
  photoValue = (float) (0.1*photoValue + 0.9*analogRead(photoRead_PIN));//Read the value from LDR
  //photoValue = analogRead(photoRead_PIN);


  //Error Calculus using the PI parameters
  error = setpoint_VALUE - photoValue;
  errorInt = errorInt + error*deltaT;
  control = Ki*errorInt + Kp*error;
  controlFilt = map((int)control, 0, 1023, 70, 255);
  PWMValue = constrain(controlFilt, 70, 255);

  //Sending the control values for the PMW PIN
  analogWrite(PWM_PIN, PWMValue);
  //analogWrite (test_PIN, controlFilt);
 
 //Read Values on Serial
  Serial.print(setpoint_VALUE);
    Serial.print("     ");
      Serial.print(photoValue);
        Serial.print("    ");
          Serial.println(PWMValue);
          
  //delay(deltaT_ms);
}
