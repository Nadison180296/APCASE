from getMessage import IOT
import numpy as np
from matplotlib import pyplot as plt
from preprocessing import functions
esp = IOT(topic="APCASE/BANCO_DE_DADOS")
esp.client.loop_start()
esp.makeDataBase()
"""f = functions()
data = np.load("database.npy")
dataP = f.transform(data)
print(np.shape(dataP))
plt.plot(dataP[:,0])
plt.show()"""
'''
f = functions()
data = np.load("database.npy")
data = f.transform(data)
plt.plot(data[:,6])
plt.show()
'''
