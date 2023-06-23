#include <Stepper.h>
#include <Servo.h>

const int pasosPorVuelta = 20;
const int velocidadMotores = 250;

//MotorX
Stepper motorX(pasosPorVuelta, 2,3,4,5);
//Motor Y
Stepper motorY(pasosPorVuelta, 6,7,8,9);

//Servo
Servo servo;
const int pinServo = 12;


void setup() {
  Serial.begin(9600);
  motorX.setSpeed(velocidadMotores);
  motorY.setSpeed(velocidadMotores);
  servo.attach(pinServo);
}


void loop() {
  if(Serial.available() > 0){
    String comunicacion = Serial.readStringUntil('\n');
    String orden = comunicacion.substring(2,3);
    String valX = comunicacion.substring(3,9);
    String valY = comunicacion.substring(10);
    
    Serial.println("-> " + orden)

    int ordenint = orden.toInt();
    int intValX = valX.toInt();
    int intValY =valY.toInt();

    if (ordenint == 1){
      servo.write(140);
    }
    else{
      servo.write(120);
    }

    motorX.step(intValX);
    motorY.step(intValY);

    Serial.println(1);
  }
}
