import serial, time


def comunicacion(archivo, puerto = "COM4"): #Recibe como datos el nombre 
    # del archivo y el puerto de conexion (VALOR POR DEFECTO COM4)
    coorfile = open(archivo, 'r')   
    mensaje = ''
    arduino = serial.Serial(puerto, 9600)
    time.sleep(2)

    for lineas in coorfile:
        linea = lineas.split(' ')
        if linea[0] == 'G01':
            mensaje = '1,'
        else:
            mensaje = '0,'

        mensaje = mensaje + ',' + linea[1] + ',' + linea[2]

        arduino.write(mensaje.encode('utf-8'))
        time.sleep(0.5)
        respuesta = arduino.readline()
        
        """ DEBE HABER UNA COMPROBACION
        LA ORDEN DEBERIA HABERSE COMPLETADO
        ANTES DE PASAR A LA SIGUIENTE
        
        if respuesta == 1: # Aqui va la comprobacion que la respuesta de arduino sea 1
            pass
        """

    arduino.close()
    coorfile.close()