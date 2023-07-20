lista = []

def setup():
    archivo = open("coordenadas.ngc", 'r')
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


def loop():
    while True:
        pass


if __name__ == "__main__":
    setup()
