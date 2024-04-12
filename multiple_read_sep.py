import time
import serial
import collections
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.lines import Line2D 
from matplotlib.widgets import Button
import numpy as np
import ctypes
from matplotlib.patches import Rectangle
import seaborn as sns
user32 = ctypes.windll.user32

def getSerialData(self, Samples,numData,serialConnection, lines):
    for i in range(numData):
        value = float(serialConnection.readline().strip()) #Lectura del puerto serie
        data[i].append(value) #Guarda lectura en la última posición
        lines[i].set_data(range(Samples),data[i])

def update_label(text, status):
    text.set_text(status)

serialPort = 'COM9'
baudRate = 9600

""""
def zoom_ax(event):
    if event.dblclick:
        ax = event.inaxes
        if ax is not None:
            if ax.get_navigate():
                ax.set_navigate(False)
                ax.autoscale_view()
            else:
                ax.set_navigate(True)
                ax.relim()
                ax.autoscale_view()
        plt.draw()
"""

try:
    serialConnection = serial.Serial(serialPort, baudRate)
except:
    print('No se puede conectar con el puerto')

Samples = 50
sampleTime = 100
numData = 3

#limites ejes
xmin  = 0
xmax = Samples
ymin = [0, 0, 0]
ymax = [1000, 500, 100]
lines = []
data = []

for i in range(numData):
    data.append(collections.deque([0] * Samples, maxlen=Samples))
    lines.append(Line2D([], [], color='blue'))

screen_width = user32.GetSystemMetrics(0)
screen_height = user32.GetSystemMetrics(1)

# Definir el aspect ratio deseado (ancho/alto)
aspect_ratio = 16 / 9  # Puedes cambiar este valor según tus preferencias

# Calcular el tamaño de la figura en función del aspect ratio y el tamaño de la pantalla
fig_width = 15
fig_height = 15

sns.set(style="darkgrid")

#ventana gui
fig = plt.figure(figsize=(fig_width / 100, fig_height / 100))
fig.set_facecolor((0.1, 0.2, 0.3))

#gráfico de lm35
ax1 = fig.add_axes([0.200, 0.10, 0.5, 0.8])
ax1.title.set_text('LM35')
ax1.set_title('ADC VISUAL',color='white')
ax1.set_xlabel("Muestras")
ax1.set_ylabel("Volt")
ax1.tick_params(axis='x', colors='white') 
ax1.tick_params(axis='y', colors='white') 
ax1.add_line(lines[0])
ax1.set_ylim(ymin[0], ymax[0])
ax1.set_xlim(xmin, xmax)

# Cambiar el color del texto de los nombres de los ejes a gris oscuro
ax1.xaxis.label.set_color('white')
ax1.yaxis.label.set_color('white')


#plt.subplots_adjust(hspace=0.5)
#plt.subplots_adjust(wspace=0.1)


rect_x = 980
rect_y = 210
rect_width = 440
rect_height = 200

x = 1450
y = 310
width = 465
height = 100

plt.draw()
anim = animation.FuncAnimation(fig,getSerialData, fargs=(Samples,numData,serialConnection,lines), interval=sampleTime)
plt.show()
serialConnection.close()

