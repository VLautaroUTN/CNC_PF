#include <SPI.h>
#include <SD.h>

#define SDpin 10

File archivo_progreso;
File archivo_coordenadas;


int leerProgreso(){
    archivo_progreso = SD.open("progreso.txt", FILE_READ);
    if (archivo_progreso){
        int progreso = toInt(archivo_progreso.seek(0);
        return progreso;
    }else {Serial.println("Error al leer el progreso")}
}


void guardarProgreso(int progreso){
    archivo_progreso = SD.open("progreso.txt", FILE_WRITE);
    if (archivo_progreso){
        archivo_progreso.seek(0);
        archivo_progreso.write(progreso);
    } else {Serial.println("Error al guardar el progreso");}
    archivo_progreso.close();
}


void iniciarTarjeta(){
    Serial.println("inicializando la tarjeta...");
    if (!SD.begin(SDpin)){
        Serial.println("Fallo en la inicializacion!");
        return;
    }
    Serial.println("Inicializacion exitosa");
}


void leerCoordenadas(){
    char caracter;
    archivo_coordenadas = SD.open("coordenadas.txt", FILE_READ);
    if (archivo_coordenadas){
        while (archivo_coordenadas.available()){
            caracter = archivo_coordenadas.read();
        }
    } else { Serial.println("error al leer las coordenadas");}
}


void dimensionarVectorDeDatos(){

}


void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
}


void loop(){
}