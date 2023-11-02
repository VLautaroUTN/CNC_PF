#include <Stepper.h>

int pasosPorVuelta =2048;

Stepper motorX(pasosPorVuelta, 2, 5, 4, 3);
Stepper motorY(pasosPorVuelta, 22, 25, 24, 23);

int pinSensorX = 40;
int pinSensorY = 41;

void puestaACero(){
    Serial.println("FUNCION puestaACero()");
        int finX = digitalRead(pinSensorX);
        int finY = digitalRead(pinSensorY);
        Serial.println("Retornando...");
        Serial.println("finX = ");
        Serial.println(finX);
        Serial.println("finY = ");
        Serial.println(finY);
        while (finX == 0){
            Serial.println("Retornando X...");
            motorX.step(10);
            finX = digitalRead(pinSensorX);
            if (finX == 1){Serial.println("Cero X alcanzado");}
        }
        while (finY == 0){
            Serial.println("Retornando Y...");
            motorY.step(10);
            finY = digitalRead(pinSensorY);
            if (finY == 1){Serial.println("Cero Y alcanzado");}
        }
}

void setup(){
    Serial.begin(9600);
    Serial.println("Retornando al cero");
    puestaACero();
  }

void loop(){}
