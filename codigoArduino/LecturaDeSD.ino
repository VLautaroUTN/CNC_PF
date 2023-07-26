#include <SD.h>
#include <SPI.h>

#define SSpin 10

File archivo;

void setup(){
    if (!SD.begin(SSpin)){return;}
    archivo = SD.open("coodenadas.ngc");
    while (archivo.available()){
        Serial.write(archivo.read());
    }
    archivo.close()
}
void loop(){

}