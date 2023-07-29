//inicio
#include <SPI.h>
#include <SD.h>

#define SDpin 10

const char* coorFileName = "coordenadas.txt";
float** arrayDeValores;


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

//NO USADA
int dimensionarListaDeDatos(){ //NO USADA Devuelve la cantidad de valores que tiene coordenadas.txt
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


void separarElementosEnLista(){
    archivo_coordenadas = SD.open(coorFileName, FILE_READ);
    int contador_de_guiones = 0;
    int numero_de_dato = 0;
    int GXY = 0; //Simboliza la posicion del dato 1er 2do o 3er posicion: G = tipo de orden, X = Coordenada x e Y= coordenada y
    String dato = "";
    char caracter;
    if (archivo_coordenadas){ //  0/39.58/143.79_   1/39.51/3.50_
        while (archivo_coordenadas.available()){
            caracter = archivo_coordenadas.read();
            if (caracter == "_"){
                arrayDeValores[contador_de_guiones][GXY] = dato.toFloat();
                dato = "";
                GXY = 0;
                contador_de_guiones++;
            }
            else{
                if(caracter == "/"){
                    arrayDeValores = new[]
                    arrayDeValores[contador_de_guiones][GXY] = dato.toFloat();
                    dato = "";
                    GXY++;
                }
                else{dato.concat(caracter);}
            }
        }
    }
    archivo_coordenadas.close();
}

void setup(){
    Serial.begin(9600);
    iniciarTarjeta();

}


void loop(){


}