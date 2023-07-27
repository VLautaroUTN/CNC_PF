#include <SPI.h>
#include <SD.h>

#define SDpin 10

String conjunto_coordenadas;
char caracter;

File archivo;

void funcionqueseparaString(){
// Esta funcion leera buscando el signo _ y el signo /
// Lo que hara es almacenar la posicion de cada uno
// creara un substring temporal que sera guardado en los valores
// x e Y,
// todo el archivo se guarda en un solo String (debo conocer el tamaño maximo disponible)
// los substring se iran actualizando con cada vuelta de reloj
// y guardaran unas nuevas coordenadas por vuelta que seran enviadas a los motores

    int numero_de_guiones = 0;

    progreso = SD.open("progreso.txt", FILE_READ);
    archivo = SD.open("coordenadas.txt", FILE_READ);
    if(archivo){        
        while (archivo.available()){
            caracter = archivo.read();
            if (caracter == "_"){
                break;
            }
            conjunto_coordenadas = concat(caracter);
        }
    }
    else{
        Serial.println("error en la lectura del archivo");
    }
    archivo.close();
}

void iniciarTarjeta(){
    Serial.println("inicializando la tarjeta...");
    if (!SD.begin(SDpin)){
        Serial.println("Fallo en la inicializacion!");
        return;
    }
    Serial.println("Inicializacion exitosa");
}


void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
}


void loop(){

}