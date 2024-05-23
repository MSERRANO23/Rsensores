import serial

i = 0
ser = serial.Serial('COM4',9600) #'/dev/ttyUSB0'
while i<5:
    dato = ser.readline().decode("utf-8")
    print(dato)
    i = i+1

print(i)
ser.close() 