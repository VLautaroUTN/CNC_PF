def leer():
    for x in range(4):
        contents = file.readline()
        print(contents)

def tipo():
    contents = file.readline()
    print(type(contents))

file = open('test.ngc', 'r')
tipo() #devuelve string :D
file.close()