#define DEBUG(a) Serial.println(a);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    String texto = Serial.readStringUntil('\n');
    Serial.println(texto);
    DEBUG(texto);
  }
}
