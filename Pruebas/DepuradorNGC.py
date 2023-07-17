"""
proceso:

proxima tarea #2: Filtrar como se elimino F pero con Z
asi despues solo tendria que filtrar entre lineas con 3 elementos y con 1

esos dos tipos ->
G00
G0x X5.000000 Y5.000000

se guardarian solo los que tengan 3 elementos

El problema es que al final de cada linea agrega un /n
¿Debo sacar ese /n? ¿Es necesario?
Objetivo: Crear a partir del archivo .ngc otro archivo
que solo contenga [bool, int, int ]
                  [servo, x ,  y  ]
"""

entrada = open('output_2_0001.ngc', 'r')
salida = open('coordenadas.ngc', 'w')


def filtrar(lista):
    for x in reversed(lista):
        if 'F' in x:
            lista.remove(x)
        elif 'Z' in x:
            lista.remove(x)
        else:
            pos = lista.index(x)
            lista[pos] = x.strip('\n')
    return lista


def buscarCoordenadas(listaContenidoPrima):
    if len(listaContenidoPrima) ==3:
        valX = listaContenidoPrima[1]
        valY = listaContenidoPrima[2]
        valores = [valX[1:7], valY[1:7]]
        return valores


def decodificar2():
    for linea in entrada:
        listaContenido = linea.split(' ') #Transformo cada linea en una lista

        if listaContenido[0] == "G00" or listaContenido[0] == "G01":
            listaContenidoFiltrada = filtrar(listaContenido)
            print(listaContenidoFiltrada)
            coordenadas = buscarCoordenadas(listaContenidoFiltrada)
            """
            if coordenadas != None:
                coordenadas.insert(0, listaContenido[0])
                print(coordenadas)
                auxiliar = 0

                for x in coordenadas:
                    auxiliar += 1
                    if auxiliar == 3:
                        salida.write(x)
                    else:
                        salida.write(x + ' ')
                salida.write('\n')
                """

if __name__ == "__main__":
    decodificar2()
    entrada.close()
    salida.close()