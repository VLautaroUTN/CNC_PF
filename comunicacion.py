import serial, time

arduino = serial.Serial('COM4', 9600)
time.sleep(2)

arduino.write('G00'.encode('utf-8'))

respuesta = arduino.readline()

print(respuesta)
arduino.close()