#include <Stepper.h>

const int pasosPorVuelta = 20;

//MotorX
Stepper motorX(pasosPorVuelta, 8,9,10,11);
Stepper motorY(pasosPorVuelta, 12,13,14,15);


void setup() {
  Serial.begin(9600);
  motorX.setSpeed(100);
  motorY.setSpeed(100);
}

void loop() {
  if(Serial.available() > 0){
    String comunicacion = Serial.readStringUntil('\n');
    String orden = comunicacion.substring(0,1);
    String valX = comunicacion.substring(3,9);
    String valY = comunicacion.substring(10);
    
    int ordenint = orden.toInt();
    float intValX = valX.toInt();
    float intValYf = valY.toInt();

    motorX.step(intValXf);
    motorY.setp(intValYf);

    Serial.println(1);
  }
}
