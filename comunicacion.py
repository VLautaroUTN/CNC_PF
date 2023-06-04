import serial, time

coorfile = open('coordenadas.ngc', 'r')   
mensaje = ''
arduino = serial.Serial('COM4', 9600)
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
    respuesta2 = arduino.readline()
    respuesta3 = arduino.readline()
    print('rta 1', respuesta)
    print('rta 2', respuesta2)
    print('rta 3', respuesta3)
    print()

arduino.close()
coorfile.close()