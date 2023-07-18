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
                        salida.write(str(x) + "_")
                    else:
                        salida.write(str(x) + "/")
                salida.write('\n')


if __name__ == "__main__":
    decodificar()
    entrada.close()
    salida.close()