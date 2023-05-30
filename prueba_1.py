entrada = open('output_2_0001.ngc', 'r')
salida = open('coordenadas.ngc', 'w')

def buscarCoordenadas(listaContenidoPrima):
    if len(listaContenidoPrima) >= 3:
        val = listaContenidoPrima[1]
        x = val[1:10]
        print('---------- ', x, '----------')

def decodificar():
    for x in range(67):
        contenido = entrada.readline()
        listaContenido = contenido.split(" ")
        
        if listaContenido[0] == "G00": #comprueba si el primer elemento es G00
            if 'F' in listaContenido[-1]: # si el ultimo elemento contiene una F lo elimina
                print('CORTANDO')
                listaContenido.pop(-1)
            #print('M', listaContenido, len(listaContenido))
            buscarCoordenadas(listaContenido) # envia la lista cortada a la funcion buscar coordenadas
        
        elif listaContenido[0] == "G01":
            if 'F' in listaContenido[-1]:
                print('CORTANDO')
                listaContenido.pop(-1)
            #print('G', listaContenido, len(listaContenido))
            buscarCoordenadas(listaContenido)

decodificar()

entrada.close()
salida.close()

""" 
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