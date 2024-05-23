import serial

ser = serial.Serial('COM4',9600) #'/dev/ttyUSB0'

i=0
j=0
with open("datos.txt", "w") as file:
    while i<27:
        dato = ser.readline().decode("utf-8").strip()
        file.write(dato+";")
        
        j=j+1
        if j==3:
            file.write("\n")
            j=0
            
        i=i+1

ser.close() 