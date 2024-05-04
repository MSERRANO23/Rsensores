import serial
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.animation as animation

tiempo = np.linspace(0,4950,100)

ser = serial.Serial('COM4', 9600)

y = []
j=0
k=0
p=0
desv = 0

fig = plt.figure()
ax = fig.add_subplot(111)

while j < 100:
    dato = (ser.readline().decode("utf-8").strip())
    dato_fl = float(dato)
    y.append(dato_fl)
    plt.plot(dato_fl)
    plt.pause(0.01)
    plt.clf()
    p = p + dato_fl
    j = j + 1

ser.close()

promedio = p/100
print("El promedio de las aceleraciones es ")
print(promedio)

while k<100:
    desv += y[k] - promedio
    k = k+1

desv_estandar = math.sqrt(desv*desv/100)
print("La desviacion estandar es de ")
print(desv_estandar)

plt.plot(y)
plt.show()