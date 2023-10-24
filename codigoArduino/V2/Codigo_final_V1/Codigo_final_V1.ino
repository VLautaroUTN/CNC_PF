#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
#include <Servo.h> 

#define SDpin 10

const char coorFileName[] = "coordenadas.txt";
const char progresoFileName[] = "progreso.txt";
int progreso;
float arrayDeValores[3];
int arrayDePasos[3];
File archivo_coordenadas = SD.open(coorFileName, FILE_READ);
File archivo_progreso = SD.open(progresoFileName, FILE_WRITE);
int tamanoArchivo = archivo_coordenadas.size();

const int pasosPorVuelta = 2048;
Stepper motorX(pasosPorVuelta, 1, 2, 3, 4);
Stepper motorY(pasosPorVuelta, 5, 6, 7, 8);
Servo servoFib;
int pinServo = 20;
int servoUp = 120;
int servoDown = 0;

int leerProgreso(){ //Lee el archivo de progreso y devuelve el valor almacenado
    if (archivo_progreso){
        archivo_progreso.seek(0);
        int progreso = archivo_progreso.read();
        return progreso;
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


void leerDatos(int progreso) { 
    /*
    Esta funcion guarda los valores de las coordenadas en Array de valores
    los valores guardados corresponden a milimetros (mm) y NO a pasos de motor
    */
    String texto = "";
    int valorDeDato = 0;
    int cantidadGuiones = 0;
    if (archivo_coordenadas) {
        while (archivo_coordenadas.available()) { 
            char caracter = archivo_coordenadas.read(); 
            if (cantidadGuiones == progreso){
                if (caracter == '_') {
                    arrayDeValores[valorDeDato] = texto.toFloat();
                    texto = "";
                    cantidadGuiones += 1;
                    guardarProgreso(cantidadGuiones);
                    break;
                }
                if (caracter == '/') {
                    arrayDeValores[valorDeDato] = texto.toFloat();
                    valorDeDato += 1;
                    texto = "";
                }
                texto.concat(caracter); // Se agrega el carácter al string 
            } else {
                if(caracter == "_"){
                    cantidadGuiones += 1;
                }
            }
        }
    } else { 
        Serial.println("Error al abrir el archivo"); 
    } 
} 


int convertirMmAPasos(float longitud){
    int pasos;
    int pasosPorMilimetro = 100;
    pasos = round(longitud / pasosPorMilimetro);
    return pasos;
}

void moverMotores(){
    if (arrayDePasos[0] == 1){
        servoFib.write(servoDown);
    }
    if (arrayDePasos[0] == 1){
        servoFib.write(servoUp);
    }
    motorX.step(arrayDePasos[1]);
    motorY.step(arrayDePasos[2]);
}

void setup(){
    Serial.begin(9600);
    iniciarTarjeta();
    servoFib.attach(pinServo);
    progreso = leerProgreso();
    motorX.setSpeed(3);
    motorY.setSpeed(3);
}


void loop(){
    leerDatos(progreso);
    for (int x =0; x < 3; x++){
        arrayDePasos[x] = convertirMmAPasos(arrayDeValores[x]);
    }
    moverMotores();
}