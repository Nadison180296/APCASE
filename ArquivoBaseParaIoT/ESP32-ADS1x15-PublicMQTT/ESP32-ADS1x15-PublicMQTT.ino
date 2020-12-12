/////////////////////////////////////////////////////////////////////////////////////////////////////
//Arquivo:   ESP32-ADS1x15-PublicMQTT;
//Autor:     Gleidson Leite;
//Tipo:      Codigo-fonte para utilizar o ESP32 através da IDE do Arduino com o ADS1x15;
//Descricao: Ler os dados da ADS1x15 e envia para o servidor via MQTT;
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <math.h>
#include <Adafruit_ADS1015.h>//Biblioteca do ADS1115
#include <WiFi.h>
#include <PubSubClient.h>
#include <stdlib.h>
Adafruit_ADS1115 ads1115(0x48);//Declaração do ADS1115

const int bufferSize = 50;//Quantidade de dados de amostra

float channel1[bufferSize];//Amostra do primeiro canal
float channel2[bufferSize];//Amostra do segundo canal

//Configurando Wifi
//const char* ssid = "Pluviometro Wireless";
//const char* password =  "96776553";
const char* ssid = "NADSON";
const char* password =  "nadison1802962016";
//Configurando Comunicação com servidor MQTT
const char* mqttServer = "m12.cloudmqtt.com";
const int mqttPort = 17367;
const char* mqttUser = "ixgbpdub";
const char* mqttPassword = "Tv6t2tMVLKQA";

WiFiClient espClient;
PubSubClient client(espClient);


void setup(void){
  Serial.begin(115200);//Inicializano ESP32
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  //client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  ads1115.begin();//Inicializando o objeto ads1115
}

//Loop do sistema
void loop(void){
  getData();
  String message = getMessage();
  client.publish("APCASE",(char*) message.c_str());
  Serial.print(message);
  //Serial.println(length(message));
  Serial.println("");
  
}

float convertToVolt(int16_t decimal){
  //Essa função retorna o valor em decimal para real
  return .1875E-3*decimal;
}

void getData(){
  //Essa função coleta os dados do primeiro e segundo canal
  int16_t ch1;
  int16_t ch2;
  
  for(int i=0;i<bufferSize;i++){
    ch1 = ads1115.readADC_SingleEnded(0);
    channel1[i] = convertToVolt(ch1); 
  }
  
  for(int i=0;i<bufferSize;i++){
    ch2 = ads1115.readADC_SingleEnded(1);
    channel2[i] = convertToVolt(ch2);  
  }  
}

float IEMG(float x[]){
  
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=fabs(x[i]);
  }
  return soma;
}

float MAV(float x[]){
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=fabs(x[i]);
  }
  soma = soma/sizeof(x);
  return soma;
}

float SSI(float x[]){
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=pow(x[i],2);
  }
  return soma;
}

float VAR(float x[]){
  
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=pow(x[i],2);
  }
  soma = soma/(sizeof(x)-1);
  return soma;
}

float RMS(float x[]){
  
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=pow(x[i],2);
  }
  soma = sqrt(soma/sizeof(x));
  return soma;
}

float LOG(float x[]){
  
  float soma = 0;
  for(int i=0;i<sizeof(x);i++){
    soma+=log(fabs(x[i]));
  }
  soma = soma/sizeof(x);
  return exp(soma);
}

float AAC(float x[]){
  float soma = 0;
  for(int i=0;i<(sizeof(x)-1);i++){
    soma+=fabs(x[i+1]-x[i]);
  }
  return soma/sizeof(x);
}

float DASDV(float x[]){
  float soma = 0;
  for(int i=0;i<(sizeof(x)-1);i++){
    soma+=pow(x[i+1]-x[i],2);
  }
  return sqrt(soma/(sizeof(x)-1));
}

float WL(float x[]){
  float soma = 0;
  for(int i=0;i<sizeof(x)-1;i++){
    soma+=fabs(x[i+1]-x[i]);
  }
  return soma;
}

float *transformData(float x[]){
  static float tData[9];
  tData[0] = IEMG(x);
  tData[1] = MAV(x);
  tData[2] = SSI(x);
  tData[3] = VAR(x);
  tData[4] = RMS(x);
  tData[5] = LOG(x);
  tData[6] = AAC(x);
  tData[7] = DASDV(x);
  tData[8] = WL(x);
  return tData;
}

String getMessage(){
  float *dataToSendCh1 = transformData(channel1);
  float *dataToSendCh2 = transformData(channel2);
  String Message = "";
  for(int i=0;i<9;i++){
    Message+=String(dataToSendCh1[i])+"|";
  }
  for(int i=0;i<9;i++){
    Message+=String(dataToSendCh2[i])+"|";
  }
  return Message;
}
