import paho.mqtt.client as mqtt
import numpy as np
import threading, time
from matplotlib import pyplot as plt

class IOT():

    def __init__(self, topic="APCASE/VARIAVEIS_ESTATISTICAS", server="m12.cloudmqtt.com", port=17367, username="ixgbpdub", password="Tv6t2tMVLKQA" ):
        self.topic = topic
        self.server = server
        self.port = port
        self.username = username
        self.password = password
        self.configClient()
        self.data = 0;
        self.status = False
        self.bd = []
        self.c = 0
        self.c1 = 0;
        self.bufferSize = 100;
        self.dataBase = []

    def configClient(self):

        self.client = mqtt.Client()
        self.client.username_pw_set(self.username, self.password)
        self.client.on_connect = self.on_connect
        self.client.on_disconnect = self.on_disconnect
        self.client.on_subscribe = self.on_subscribe
        self.client.on_message = self.on_message

        self.client.connect(self.server, self.port)
        #self.client.loop_start()

    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result: " + mqtt.connack_string(rc))
        self.client.subscribe(topic=self.topic)

    def on_disconnect(self, client, userdata, rc):
        if rc!=0:
            print("Unexpected disconnection")

    def on_subscribe(self, client, userdata, mid, granted_qos):
        print("Subscribed to topic: " + self.topic)

    def on_message(self, client, userdata, msg):
        #print("Received message: " + msg.topic + " " + str(msg.payload))
        if str(msg.payload!=self.data):
            self.status = True
            x = msg.payload#np.fromstring(msg.payload,dtype=Str, sep="|")
            self.data = self.convertData(x)
            self.c+=1
        self.status = False
    
    def convertData(self,x):
        x = str(x).replace("b'","").replace("\'","").split('|')
        data = []
        for i in range(len(x[0:-1])):
            data.append(int(x[i], 16))
        return data
    
    def makeDataBase(self):
        if self.c==0:
            self.c1 = self.c
            if self.data!=0:
                self.dataBase.append(self.data)
        elif self.c!=self.c1:
            self.c1 = self.c
            self.dataBase.append(self.data)
            print(len(self.dataBase))
            if len(self.dataBase)>=self.bufferSize:
                print(self.dataBase)
                teste = np.asarray(self.dataBase)*.5E-3
                np.save("database.npy",teste)
                teste = teste.reshape(-1,1)
                plt.plot(teste)
                plt.show()
                self.c = 0
                exit();
                
        self.thread = threading.Timer(.01, self.makeDataBase)
        self.thread.start();
