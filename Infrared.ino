/*

Código para medição da distância a partir da resposta 
do par emissor/receptor infravermelho

*/

int IRsensor = A0;
int duration = 2000; // duration of the calibration phases

// Variables to s tore the results of calibration
int calibrationZero;
int calibrationOne;

int getDistanceReading (int readings = 5) {
 int sensorCumulativeValue = 0;
 for (int i = 0; i < readings; i ++) {
 delay(20);
 sensorCumulativeValue += analogRead(IRsensor);
 }
 
 int distance = map
      (
        sensorCumulativeValue / readings,
        calibrationZero, calibrationOne,
        0, 255
      );
 return constrain(distance, 255, 0);
}

void setup() {
  pinMode(IRsensor, INPUT);
  Serial.begin(9600);

  // Far
  Serial.println("Far calibration...");
  delay(duration);

  double sensorCumulativeValue = 0;
  double reads = 0;
  unsigned long timeStart = millis();

  
  do {
    delay(20);
    sensorCumulativeValue += analogRead(IRsensor);
    reads++;
  } while(millis()<= timeStart + duration);
  calibrationZero = sensorCumulativeValue / reads;

  
  Serial.println(calibrationZero);
  
  // Close
  Serial.println("Close calibration...");
  delay(duration);

  sensorCumulativeValue = 0;
  reads = 0;
  timeStart = millis();
  do{
    delay(20);
    sensorCumulativeValue += analogRead(IRsensor);
    reads++;    
  }while (millis()<= timeStart + duration);
  calibrationOne = sensorCumulativeValue / reads;

  Serial.println(calibrationOne);
 /*  for (int i= 0; i<1; i++){ 
  int distance = getDistanceReading ();
  Serial.println(distance);
  delay(500);}
}*/}

void loop() {
 int distance = getDistanceReading ();
  Serial.println(distance);
  delay(500);}
