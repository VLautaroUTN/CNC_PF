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
    int intValY =valY.toInt();

    if (orden == 1){
       servo.write(140);
    }
    else{
        servo.write(120);
    }

    motorX.step(intValX);
    motorY.setp(intValY);

    Serial.println(1);
  }
}
