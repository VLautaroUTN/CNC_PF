void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    String comunicacion = Serial.readStringUntil('\n');
    String orden = comunicacion.substring(0,1);
    String valX = comunicacion.substring(3,9);
    String valY = comunicacion.substring(10);
    
    int ordenint = orden.toInt();
    float valXf = valX.toFloat();
    float valYf = valY.toFloat();
  }
}
