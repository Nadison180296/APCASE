from PythonADS1x15RecebeMQTTgetMessage import IOT
from matplotlib import pyplot as plt
import numpy as np
esp = IOT()
buffer = 100
data = []
esp.client.loop_start()
x = 0;
for i in range(buffer):
    x = esp.data
    while isinstance(esp.data, int):
        continue
    while np.array_equal(x, esp.data):
        continue
    data.append(esp.data)
    print(i)
esp.client.loop_stop()
data = np.asarray(data)
plt.plot(data[:,0])
plt.show()
fileName = "Arquivo.npy"
np.save(fileName, data)
