#include <SPI.h>
#include <SD.h>
#include <Stepper.h>
#include <Servo.h> 
//comentario random para commitear - BORRAR ESTE COMENTARIO
#define SDpin 53 

const char coorFileName[] = "coordenadas.txt";
const char progresoFileName[] = "progreso.txt";
int progreso;
int longitudDeCoordenadas;
float arrayDeValores[3];
int arrayDePasos[3];
int inicioTarjetaExitoso = 0;
int inicioLecturaProgreso = 0;
int puestaACeroExitosa = 0;
File archivo_coordenadas = SD.open(coorFileName, FILE_READ);
File archivo_progreso = SD.open(progresoFileName, FILE_WRITE);
Servo servoFib;


const int pasosPorVuelta = 2048;


Stepper motorX(pasosPorVuelta, 2, 5, 4, 3);
Stepper motorY(pasosPorVuelta, 22, 25, 24, 23);
int pinServo = 6;
int pinLeds = 7;
int pinSensorX = 40;
int pinSensorY = 41;
// pines que no se definen - Tarjeta SD
/*  PARA ARDU UNO
cs = 10
sck = 13
miso = 12
mosi = 11
*/


int leerProgreso(){ //Lee el archivo de progreso y devuelve el valor almacenado
    Serial.println("FUNCION leerProgreso()");
    if (archivo_progreso){
        archivo_progreso.seek(0);
        int progreso = archivo_progreso.read();
        return progreso;
    }else {Serial.println("Error al leer el progreso");}
}


void guardarProgreso(int progreso){
    Serial.println("FUNCION guardarProgreso()");
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
    Serial.println("FUNCION inicializarTarjeta()");
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


void leerDatos(int progreso) { 
    Serial.println("FUNCION leerDatos()");
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
        Serial.println("Error al abrir el archivo_coordenadas"); 
    } 
} 


int convertirMmAPasos(float longitud){
    Serial.println("FUNCION convertirMmAPasos()");
    int pasos;
    int pasosPorMilimetro = 100;
    pasos = round(longitud / pasosPorMilimetro);
    return pasos;
}


void moverMotores(){
    Serial.println("FUNCION moverMotores()");
    int servoUp = 120;
    int servoDown = 0;
    if (arrayDePasos[0] == 1){
        servoFib.write(servoDown);
    }
    if (arrayDePasos[0] == 1){
        servoFib.write(servoUp);
    }
    motorX.step(arrayDePasos[1]);
    motorY.step(arrayDePasos[2]);
}


int medirLongitudDeOrdenes(){
    Serial.println("FUNCION medirLongitudDeOrdenes()");
    /*
    Esta funcion lee el archivo "coordenadas.txt" y busca todos los guiones
    Para devolver la cantidad de instrucciones que posee y asi poder
    calcular el progreso para los LEDs indicadores
    */
    int longitud = 0;
    if (archivo_coordenadas) {
            while (archivo_coordenadas.available()) { 
                char caracter = archivo_coordenadas.read();
                if (caracter == "_"){
                    longitud += 1;
                }
            }
            archivo_coordenadas.seek(0);
            return longitud;
    }
}


void actualizarPanelLed(){
    Serial.println("FUNCION actualizarPanelLed()");
    int porcentajeDeProgreso = round(progreso / longitudDeCoordenadas) * 100;
    switch (porcentajeDeProgreso){
        case 25:
            digitalWrite(pinLeds, HIGH);
            delay(200);
            digitalWrite(pinLeds, LOW);
            break;

        case 50:
            digitalWrite(pinLeds, HIGH);
            delay(200);
            digitalWrite(pinLeds, LOW);
            break;

        case 75:
            digitalWrite(pinLeds, HIGH);
            delay(200);
            digitalWrite(pinLeds, LOW);
            delay(200);
            digitalWrite(pinLeds, HIGH);
            delay(200);
            digitalWrite(pinLeds, LOW);
            break;

        case 100:
            digitalWrite(pinLeds, HIGH);
            delay(1000);
            digitalWrite(pinLeds, LOW);
            break;
    }
    
}


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
    // Definicion de pines
    //motores pines
    pinMode(pinServo, OUTPUT);
    pinMode(pinLeds, OUTPUT);
    pinMode(pinSensorX, INPUT);
    pinMode(pinSensorY, INPUT);
    // Otras definiciones
    Serial.begin(9600);
    Serial.println("inicializando");
    iniciarTarjeta();
    servoFib.attach(pinServo);
    progreso = leerProgreso();
    motorX.setSpeed(3);
    motorY.setSpeed(3);
    longitudDeCoordenadas = medirLongitudDeOrdenes();
    Serial.println("Retornando al cero");
    puestaACero();
    Serial.println("Iniciaalizacion terminada");
}


void loop(){
    Serial.println("FUNCION loop()");
    leerDatos(progreso);
    for (int x =0; x < 3; x++){
        arrayDePasos[x] = convertirMmAPasos(arrayDeValores[x]);
    }
    moverMotores();
    actualizarPanelLed();
}
