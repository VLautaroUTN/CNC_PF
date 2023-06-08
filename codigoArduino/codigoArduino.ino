#include <Stepper.h>

const int pasosPorVuelta = 20;
const velocidadMotores = 250;

//MotorX
Stepper motorX(pasosPorVuelta, 8,9,10,11);
//Motor Y
Stepper motorY(pasosPorVuelta, 12,13,14,15);


void setup() {
  Serial.begin(9600);
  motorX.setSpeed(velocidadMotores);
  motorY.setSpeed(velocidadMotores);
}


void loop() {
  if(Serial.available() > 0){
    String comunicacion = Serial.readStringUntil('\n');
    String orden = comunicacion.substring(0,1);
    String valX = comunicacion.substring(3,9);
    String valY = comunicacion.substring(10);
    
    int ordenint = orden.toInt();
    int intValX = valX.toInt();
    int intValYf = valY.toInt();

    motorX.step(intValXf);
    motorY.setp(intValYf);

    Serial.println(1);
  }
}
