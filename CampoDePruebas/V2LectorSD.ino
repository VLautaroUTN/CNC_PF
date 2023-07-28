//inicio
#include <SPI.h>
#include <SD.h>

#define SDpin 10

const char* coorFileName = "coordenadas.txt";

File archivo_progreso;
File archivo_coordenadas;


int leerProgreso(){
    File archivo_progreso = SD.open(coorFileName, FILE_READ);
    if (archivo_progreso){
        archivo_progreso.seek(0);
        int progreso = archivo_progreso.read();
        return progreso;
    }else {Serial.println("Error al leer el progreso");}
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


int dimensionarVectorDeDatos(){ // Devuelve la cantidad de valores que tiene coordenadas.txt
    int longitudDeDatos = 0;
    archivo_coordenadas = SD.open(coorFileName, FILE_READ);
    if (archivo_coordenadas){
        while (archivo_coordenadas.available()){
            if (archivo_coordenadas.read() == "_"){
                longitudDeDatos++;
            }
        }
    }
    archivo_coordenadas.close();
    return longitudDeDatos;
}


void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
    int arrayDeValores[dimensionarVectorDeDatos()];
}


void loop(){


}