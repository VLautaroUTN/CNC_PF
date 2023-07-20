#Este archivo lee las coordenadas y las segmenta para su uso
#Es de prueba ya que el sketch final debe estar en formato .ino
lista = []
datos = []

def setup():
    archivo = open("coordenadas.ngc", 'r')
    #archivo_progreso = open("progreso.txt, w")
    elemento = ""
    while True:
        letra = archivo.read(1) #Lee de a 1 caracter por vez

        if not letra: break # Se comporta como el archivo.available()

        if letra == "_": #  Si la letra es un guion se guarda el string "elemento"
                        # en una lista y posteriormente se reinicia elemento a vacio
            lista.append(elemento)
            elemento = ""
        else:
            elemento += letra
    archivo.close()


def loop():
    progreso = 0
    while True:
        datos = lista[progreso].split("/")
        print(datos)
        progreso += 1



if __name__ == "__main__":
    setup()
    loop()