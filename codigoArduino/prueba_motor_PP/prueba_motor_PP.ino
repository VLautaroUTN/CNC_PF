#include <Stepper.h>

const int stepsPerRevolution = 2048;  // Número de pasos por revolución del motor
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);  // Conexiones del motor stepper a los pines 8, 9, 10 y 11

void setup() {
  Serial.begin(9600);  // Inicializar el puerto serie a 9600 baudios
  myStepper.setSpeed(3);
}

void loop() {
  if (Serial.available()) {
    int steps = Serial.parseInt();  // Leer el número recibido por el puerto serie
    myStepper.step(steps);
    }
}