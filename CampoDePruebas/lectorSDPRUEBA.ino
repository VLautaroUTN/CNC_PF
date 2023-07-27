#include <SPI.h>
#include <SD.h>

#define SDpin 10

String conjunto_coordenadas;
char caracter;

File archivo;

int leerProgreso(){
    archivo_progreso = SD.open("progreso.txt", FILE_READ);
    if (archivo_progreso){
        int progreso = archivo_progreso.seek(0);
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


void funcionqueseparaString(){
// Esta funcion leera buscando el signo _ y el signo /
// Lo que hara es almacenar la posicion de cada uno
// creara un substring temporal que sera guardado en los valores
// x e Y,
// todo el archivo se guarda en un solo String (debo conocer el tamaño maximo disponible)
// los substring se iran actualizando con cada vuelta de reloj
// y guardaran unas nuevas coordenadas por vuelta que seran enviadas a los motores

    archivo_coordenadas = SD.open("coordenadas.txt", FILE_READ);
    if(archivo_coordenadas){        
        while (archivo_coordenadas.available()){
            caracter = archivo.read();
            if (caracter == "_"){
                break;
            }
            conjunto_coordenadas = concat(caracter);
        }
    } else { Serial.println("error al leer las coordenadas");}
    archivo_coordenadas.close();
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