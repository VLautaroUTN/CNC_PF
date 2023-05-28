file = open('test.ngc', 'r')

def leer():
    for x in range(4):
        contents = file.readline()
        print(contents)
        file.close()

def tipo():
    contents = file.readline()
    print(type(contents))
    file.close()



"""------------------------------------------------------------------
Método string split

El split() function, es usado usualmente para dividir strings.
El  método split()

Template: string.split(separador, maxdivision)

separador: El delimitador del string. Tú divides el string basado en estos caracteres. Por ejemplo (" "), (":"), (";"), etc.

maxdivision: El número de veces a dividir el string basados en el separador. Si, no especificamos éste número o ponemos -1, el string tomara todas las occurrencias del separator.

Este metodo retorna una lista de substrings delimitados por el separator.
Ejemplos

String dividido con espacio en blanco " "

string = "freeCodeCamp is fun."
print(string.split(" "))

Delimitador (" ") - Python3.7

Resultado:

['freeCodeCamp', 'is', 'fun.']
"""