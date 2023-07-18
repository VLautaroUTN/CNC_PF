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
            lista[pos] = x.strip('XY\n')

    if lista[0] == "G00":
        lista[0] = 0
    else:
        lista[0] = 1
    if len(lista) == 3:
        return lista

# Capaz pueda usar esta misma funcion para filtrar y retornar las coordenadas


def decodificar():
    for linea in entrada:
        listaContenido = linea.split(' ') #Transformo cada linea en una lista

        if listaContenido[0] == "G00" or listaContenido[0] == "G01":
            listaContenidoFiltrada = filtrar(listaContenido)

            if listaContenidoFiltrada != None:
                variableAuxiliar = 0
                for x in listaContenidoFiltrada:
                    variableAuxiliar += 1
                    if not variableAuxiliar == 1:
                        x = float(x)
                        x = "{:.2f}".format(x)
                    if variableAuxiliar == 3:
                        salida.write(x)
                    else:
                        salida.write(str(x) + "/")
                salida.write('\n')


if __name__ == "__main__":
    decodificar()
    entrada.close()
    salida.close()