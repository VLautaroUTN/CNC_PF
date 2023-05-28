file = open('output_2_0001.ngc', 'r')

def buscarCoordenadas(listaContenidoPrima):
    x_valor = None
    y_valor = None
    for val in listaContenidoPrima:
        if 'X' in val:
            x_valor = val
        if 'Y' in val:
            y_valor = val
    return x_valor, y_valor


def decodificar():
    for x in range(67):
        contenido = file.readline()
        listaContenido = contenido.split(" ")
        #print(listaContenido[0])
        if listaContenido[0] == "G00":
            #print("MOVIMIENTO")
            buscarCoordenadas(listaContenido)
        elif listaContenido[0] == "G01":
            #print("GRABADO")
            buscarCoordenadas(listaContenido)

def test():
    for linea in file.readlines():
        listaContenido = linea.split(" ")
        ordenes = []
        try:
            ordenes = [listaContenido[0], listaContenido[1], listaContenido[2]]
        except:
            print("no linea de ordenes")
        print(ordenes)


def test2():
    cantLineas = 0
    for lineas in file.readlines():
        cantLineas += 1
    for x in range(cantLineas):
        asd

test2()
