#LINK PARA O ORIGINAL => https://www.filipeflop.com/blog/raspberry-pi-controlar-o-nodemcu-parte-1/
#                        https://imasters.com.br/desenvolvimento/brincando-com-raspberry-pi-arduino-nodemcu-e-mqtt

#Programa: Controlar o Nodemcu usando Raspberry Pi

import paho.mqtt.client as mqtt
import sys
from Tkinter import *
from threading import Thread
 
#Variaveis e objetos globais
janela = Tk()  #objeto que representa a janela / GUI
 
#definicoes: 
client = mqtt.Client()
Broker = "iot.eclipse.org"
PortaBroker = 1883
KeepAliveBroker = 60
TimeoutConexao = 5 #em segundos
TopicoPublish = "MQTTDisplayRaspPi"  #substitua este topico por algum de sua escolha (de preferencia, algo "unico" pra voce)
 
########
#Eventos
########
def EventoBotao1():
    global client
 
    print "[BOTAO] Botao 1 pressionado!"
        client.publish(TopicoPublish,"BT1")
    return
 
def EventoBotao2():
    global client
 
    print "[BOTAO] Botao 2 pressionado!"
        client.publish(TopicoPublish,"BT2")
    return
 
def EventoBotao3():
    global client
 
    print "[BOTAO] Botao 3 pressionado!"
        client.publish(TopicoPublish,"BT3")
    return
 
def EventoBotao4():
    global client
 
    print "[BOTAO] Botao 4 pressionado!"
        client.publish(TopicoPublish,"BT4")
    return
 
def EventoBotao5():
    global client
 
    print "[BOTAO] Botao 5 pressionado!"
        client.publish(TopicoPublish,"BT5")
    return
 
def FinalizaPrograma():
    global client
 
    print "O programa esta sendo finalizado."
    client.disconnect()
    janela.destroy()
    sys.exit(0)
 
###########################
#Funcao de desenho de tela
###########################
def DesenhaTela():
    global janela
 
    # - coloca o titulo da janela como 'GUI - Python'
    # - muda sua cor de fundo
        # - define o tamanho da janela (nesse caso, 480x320, mesma resolucao do display)
    # - faz com que a janela seja posicionada no meio da tela 
    # - coloca botoes na tela
        # - Coloca o logo FilipeFlop
 
    janela.title("GUI - Python")
    janela.configure(bg='#3F3F3F')
    width=480
    height=320
    screen_width = janela.winfo_screenwidth()
        screen_height = janela.winfo_screenheight()
    xCentro = (screen_width/2) - (width/2)
        yCentro = (screen_height/2) - (height/2)
    janela.geometry('%dx%d+%d+%d' % (width, height, xCentro, yCentro))
 
        #widgets
        label1 = Label(text="Blog FilipeFlop", fg='#00E0F9', bg='#3F3F3F', font=("Helvetica",12) )
        label1.grid(row = 1, column = 1, padx=5, pady=5)
 
 
    botao1 = Button(janela, text='Botao 1', command = EventoBotao1, height=5, width=15)
        botao1.grid(row = 11, column = 1, padx=5, pady=5)
 
    botao2 = Button(janela, text='Botao 2', command = EventoBotao2, height=2, width=15)
        botao2.grid(row = 21, column = 1, padx=5, pady=5)
 
    botao3 = Button(janela, text='Botao 3', command = EventoBotao3, height=1, width=15)
        botao3.grid(row = 1, column = 16, padx=5, pady=5)
 
    botao4 = Button(janela, text='Botao 4', command = EventoBotao4, height=5, width=15)
        botao4.grid(row =11, column = 16, padx=5, pady=5)
 
    botao5 = Button(janela, text='Botao 5', command = EventoBotao5, height=2, width=15)
        botao5.grid(row = 21, column = 16, padx=5, pady=5)
 
    #associa funcao ao fechamento da janela (evento de fechamento)
        janela.protocol('WM_DELETE_WINDOW', FinalizaPrograma)
 
    return
 
 
#Callback - conexao ao broker realizada
def on_connect(client, userdata, flags, rc):
    print("[STATUS] Conectado ao Broker. Resultado de conexao: "+str(rc))
    return
 
#Callback - mensagem recebida do broker
def on_message(client, userdata, msg):
    MensagemRecebida = str(msg.payload)
        print("[MSG RECEBIDA] Topico: "+msg.topic+" / Mensagem: "+MensagemRecebida)
    return
 
 
#programa principal:
 
#inicializa MQTT
print("[STATUS] Inicializando MQTT...")
client.on_connect = on_connect
client.on_message = on_message
client.connect(Broker, PortaBroker, KeepAliveBroker)
 
#incializa tela
DesenhaTela()
 
#inicializa thread de mqtt
ThMQTT = Thread(target=client.loop_forever)
ThMQTT.start()
 
janela.mainloop()