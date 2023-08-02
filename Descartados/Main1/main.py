from comunicacion.py import *

def interfazCMD():
    print("Bienvenido al Control CNC")
    print(" -- Creado por VOKMS --")
    while True:
        print("Elija una opción")
        print("1- Enviar ordenes a CNC")
        print("2- Preparar ordenes desde un Gcode")
        print("3- Seleccionar archivo")
        print("9- Ayuda")
        print("0- Salir")

        eleccion = input("-> ")
        if eleccion == "1":
            pass
        elif eleccion == "2":
            pass
        elif eleccion == "0":
            print("Gracias por ocupar nuestros servicios")
            break
        else:
            print("Opción invalida")


if __name__ == "__main__":
    interfazCMD()