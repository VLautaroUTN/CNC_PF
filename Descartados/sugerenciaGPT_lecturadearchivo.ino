#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; // Pin del Arduino conectado al CS de la tarjeta SD
const char* fileName = "coordenadas.txt"; // Nombre del archivo

void setup() {
  Serial.begin(9600);

  // Inicializar la comunicación con la tarjeta SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Error al inicializar la tarjeta SD.");
    return;
  }

  // Contar la cantidad de guiones bajos en el archivo
  int numValues = 0;
  File file = SD.open(fileName);
  if (file) {
    while (file.available()) {
      if (file.read() == '_') { // Si se encuentra un guion bajo
        numValues++; // Incrementar el contador
      }
    }
    file.close();
  } else {
    Serial.println("Error al abrir el archivo.");
    return;
  }

  // Crear un vector dinámico con el tamaño adecuado
  int* values = new int[numValues];

  // Leer el archivo y almacenar los valores en el vector
  file = SD.open(fileName);
  int valueCount = 0;
  if (file) {
    while (file.available()) {
      String data = file.readStringUntil('_'); // Leer hasta el guion bajo
      int value = data.toInt(); // Convertir el valor a entero (int)
      values[valueCount] = value; // Almacenar el valor en el vector
      valueCount++;
    }
    file.close();

    // Aquí puedes utilizar el vector "values" que contiene todos los valores leídos del archivo

    // Ejemplo: Imprimir los valores leídos
    for (int i = 0; i < numValues; i++) {
      Serial.print("values[" + String(i) + "] = " + String(values[i]) + " ");
    }
    Serial.println();

    // Recuerda liberar la memoria del vector dinámico una vez que ya no lo necesites
    delete[] values;
  } else {
    Serial.println("Error al abrir el archivo.");
  }
}

void loop() {
  // Tu código principal aquí, si es necesario
}
