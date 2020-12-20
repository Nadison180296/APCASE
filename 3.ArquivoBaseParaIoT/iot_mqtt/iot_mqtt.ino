#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include <WiFi.h>
#include <PubSubClient.h>

//Configurações do ADS1015
Adafruit_ADS1015 ads;
float v = 0.0;
int16_t adc0;
String voltageString;
String Message = "";
int bufferSize = 100;

// The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
// ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

//Configurações do Wifi
const char* ssid = "Pluviometro Wireless";
const char* password =  "96776553";

//Configurações do Broker
const char* mqttServer = "m12.cloudmqtt.com";
const int mqttPort =  17367;
const char* mqttUser = "ixgbpdub";
const char* mqttPassword = "Tv6t2tMVLKQA";
const char* esp32Client = "ESP32";
const char* topico = "APCASE/BANCO_DE_DADOS";

//Declaração do objeto pubsubclient
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  wifiConnect();
  client.setServer(mqttServer, mqttPort);
  mqttConnect();
  client.setCallback(callback);
  client.subscribe(topico);

  ads.setGain(GAIN_FOUR);
  ads.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  createDataBase();
}

void wifiConnect(){
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("Conectando ao WiFi");
  }
  Serial.println("Conectado a rede Wifi");
}

void mqttConnect(){
  while(!client.connected()){
    Serial.println("Conectando ao servidor MQTT");
    if(client.connect(esp32Client,mqttUser,mqttPassword)){
      Serial.println("Conectado");
    }else{
      Serial.print("Falha na conexão com o Broker, status: ")/
      Serial.println(client.state());
      delay(2000);
      }
  }
}

void getData(){
  adc0 = ads.readADC_SingleEnded(0);
  voltageString = String(adc0,HEX);
}

void createDataBase(){
  for(int i=0; i<bufferSize;i++){
    getData();
    Message+=voltageString+"|";
  }
  //Serial.println(Message);
  client.publish(topico, (char*) Message.c_str());
  Message = "";
}
//Função para tratamento dos dados recebidos
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensagem recebida do topico: ");
  Serial.println(topic);
  Serial.print("Mensagem: ");

  for(int i=0; i<length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}
