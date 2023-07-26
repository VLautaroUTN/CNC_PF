#include <SPI.h>
#include <SD.h>

#define SDpin 10

String coordenadas;
char caracter

File archivo;

void funcionqueseparaString(){}
// Esta funcion leera buscando el signo _ y el signo /
// Lo que hara es almacenar la posicion de cada uno
// creara un substring temporal que sera guardado en los valores
// x e Y,
// todo el archivo se guarda en un solo String (debo conocer el tamaño maximo disponible)
// los substring se iran actualizando con cada vuelta de reloj
// y guardaran unas nuevas coordenadas por vuelta que seran enviadas a los motores



void setup(){
    Serial.begin(9600);
    Serial.println("inicializando la tarjeta...");
    if (!SD.begin(SDpin)){
        Serial.println("Fallo en la inicializacion!");
        return;
    }
    Serial.println("Inicializacion exitosa");

    archivo = SD.open("coordenadas.txt", FILE_READ);
    if (archivo){
      while (archivo.available()){
          caracter = archivo.read();
          if(){}
      }
    }
    else{
        Serial.println("error en la lectura del archivo");
    }
}

void loop(){

}