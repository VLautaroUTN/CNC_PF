#include <SPI.h>
#include <SD.h>

#define SDpin 10

const char coorFileName[] = "coordenadas.txt";
const char progresoFileName[] = "progreso.txt";
int progreso;
float arrayDeValores[3];
File archivo_coordenadas = SD.open(coorFileName, FILE_READ);

int leerProgreso(){
    File archivo_progreso = SD.open(coorFileName, FILE_READ);
    if (archivo_progreso){
        archivo_progreso.seek(0);
        int progreso = archivo_progreso.read();
        return progreso.toInt();
    }else {Serial.println("Error al leer el progreso");}
}


void guardarProgreso(int progreso){
    /*  
Función para guardar el progreso en un archivo de texto llamado "progreso.txt" en la tarjeta SD. 
Recibe como parámetro el valor del progreso a guardar. 
Si se puede abrir el archivo de progreso, se posiciona al principio y se escribe el valor del progreso. 
Si no se puede abrir el archivo, se muestra un mensaje de error. 
Finalmente, se cierra el archivo. 
*/
    archivo_progreso = SD.open("progreso.txt", FILE_WRITE);
    if (archivo_progreso){
        archivo_progreso.seek(0);
        archivo_progreso.write(progreso);
    } else {Serial.println("Error al guardar el progreso");}
    archivo_progreso.close();
}


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
}


void leerDatos(File archivo, int progreso) { 
    char texto = "";
    int valorDeDato = 0;
    int cantidadGuiones = 0;
    if (archivo) {
        while (archivo.available()) { 
            char caracter = archivo.read(); 
            if (cantidadGuiones == progreso){
                if (caracter == '_') {
                    arrayDeValores[valorDeDato] = texto.toFloat();
                    texto = "";
                    cantidadGuiones += 1;
                    guardarProgreso(cantidadGuiones);
                    break
                }
                if (caracter == '/') {
                    arrayDeValores[valorDeDato] = texto.toFloat();
                    valorDeDato += 1;
                    texto = "";
                }
                texto += caracter; // Se agrega el carácter al string 
            } else {
                if(caracter == "_"){
                    cantidadGuiones += 1;
                }
            }
        }
        archivo.close();
    } else { 
        Serial.println("Error al abrir el archivo"); 
    } 
} 


void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
    progreso = leerProgreso()
}


void loop(){
    leerDatos(archivo_coordenadas, progreso);

}