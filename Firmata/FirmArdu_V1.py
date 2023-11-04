from pyfirmata import ArduinoMega, util


def moverMotores(lista):
    pinMX = [2, 3, 4, 5]
    pinMY = [20, 21, 22, 23]
    pinServo = 11

    if lista[0] == 1:
        pass


    if pasos > 0:
        for x in pasos:
            #  Aqui va toda la logica para girar los motores
            pass
    if pasos < 0:
        for x in pasos:
            #  Aqui tambien
            pass
    else:
        print("Error en la lectura de los pasos")


def LeerCoorTxt():
    file = open("coordenadas.txt", "r")
    listaDimensiones = []
    for x in file:
        listaIntermediaDimensionesMM = x.split("_")
        del listaIntermediaDimensionesMM[-1]
        for valor in listaIntermediaDimensionesMM:
            lista = valor.split('/')
            del lista[-1]
            listaDimensiones.append(lista)
    del listaIntermediaDimensionesMM
    del lista
    return listaDimensiones


def convertirMmAPasos(distancia):
    mmPorPasos = 1000
    pasos = distancia / mmPorPasos
    return pasos


def firmataTest():

    # Configurar la conexión con el Arduino Mega
    board = ArduinoMega('COM9')  # Reemplaza '/dev/ttyUSB0' con el puerto correspondiente a tu placa

    # Iterar sobre los pines digitales
    for pin in board.digital:
        print("Leyendo el estado del pin", pin.pin_number)
        print(pin.read())

    # Iterar sobre los pines analógicos
    for pin in board.analog:
        print("Leyendo el valor analógico del pin", pin.pin_number)
        print(pin.read())

    # Cerrar la conexión con el Arduino Mega
    board.exit()


if __name__ == "__main__":
    firmataTest()