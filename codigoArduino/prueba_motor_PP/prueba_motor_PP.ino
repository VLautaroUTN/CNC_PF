#include <Stepper.h>

const int stepsPerRevolution = 200;  // Número de pasos por revolución del motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // Conexiones del motor stepper a los pines 8, 9, 10 y 11

void setup() {
  Serial.begin(9600);  // Inicializar el puerto serie a 9600 baudios
}

void loop() {
  if (Serial.available() > 0) {
    int steps = Serial.parseInt();  // Leer el número recibido por el puerto serie

    // Girar el motor stepper la cantidad de pasos recibida
    if (steps > 0) {
      myStepper.setSpeed(300);  // Velocidad de rotación del motor (ajustable según tus necesidades)
      myStepper.step(steps);
    }
  }
}