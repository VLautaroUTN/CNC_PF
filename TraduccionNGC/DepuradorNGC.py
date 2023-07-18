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


def decodificar():
    for linea in entrada:
        lista_contenido = linea.split(' ')  # Transformo cada linea en una lista

        if lista_contenido[0] == "G00" or lista_contenido[0] == "G01":
            lista_contenido_filtrada = filtrar(lista_contenido)

            if lista_contenido_filtrada is not None:
                variable_auxiliar = 0
                for x in lista_contenido_filtrada:
                    variable_auxiliar += 1
                    if not variable_auxiliar == 1:
                        x = float(x)
                        x = "{:.2f}".format(x)
                    if variable_auxiliar == 3:
                        salida.write(str(x) + "_")
                    else:
                        salida.write(str(x) + "/")
                salida.write('\n')


if __name__ == "__main__":
    decodificar()
    entrada.close()
    salida.close()
