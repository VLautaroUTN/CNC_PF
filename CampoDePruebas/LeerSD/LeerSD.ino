#include <SPI.h>
#include <SD.h>

File archivo_coordenadas = SD.open(coorFileName, FILE_READ);

#define SDpin 53 


void iniciarTarjeta(){
    /*
    El código muestra una función llamada "iniciarTarjeta" que inicializa una tarjeta SD
    y verifica si la inicialización fue exitosa o no. Si la inicialización falla, se imprimirá
    un mensaje de error. Si tiene éxito, se imprimirá un mensaje de confirmación.
    */
    Serial.println("inicializando la tarjeta...");
    if (!SD.begin(SDpin)){
        Serial.println("Fallo en la inicializacion!");
        return;
    }
    Serial.println("Inicializacion exitosa");
    inicioConExito = 1;
}

void leerDatos(){
    if (archivo_coordenadas) {
        while (archivo_coordenadas.available()) { 
            char caracter = archivo_coordenadas.read();
            Serial.println(caracter);
        }
    }
}

void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
}

void loop(){
    leerDatos()
}