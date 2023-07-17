#Este archivo lee las coordenadas y las segmenta para su uso
#Es de prueba ya que el sketch final debe estar en formato .ino

def setup():
    archivo = open("coordenadas.ngc", 'r')
    while True:
        letra = archivo.read(1) #Lee de a 1 caracter por vez
        if not letra: break # Se comporta como el archivo.available()
        print(letra)


def loop():
    while True:
        pass

if __name__ == "__main__":
    setup()
    #loop()