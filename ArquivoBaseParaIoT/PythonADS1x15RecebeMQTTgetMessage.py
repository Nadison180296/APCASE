import paho.mqtt.client as mqtt
import numpy as np


class IOT():

    def __init__(self, topic="APCASE", server="m12.cloudmqtt.com", port=17367, username="ixgbpdub", password="Tv6t2tMVLKQA" ):
        self.topic = topic
        self.server = server
        self.port = port
        self.username = username
        self.password = password
        self.configClient()
        self.data = 0;

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
        print("Received message: " + msg.topic + " " + str(msg.payload))
        if str(msg.mqtt!=self.data):
            self.data = np.fromstring(msg.payload,dtype=float, sep="|")
            #print(self.data)
