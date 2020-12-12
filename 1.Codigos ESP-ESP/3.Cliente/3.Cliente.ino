#include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU
#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

  const String  ClientType       = "Cliente 01";

  char*         ESPssid;            // Wifi Name
  char*         ESPpassword;        // Wifi Password

  int             ESPServerPort  = 9001;
  IPAddress       ESPServer(192,168,4,1);
  WiFiClient      ESPClient;
  String Dado0;String Dado00;
  String Dado1;String Dado11;
  String Dado2;String Dado22;
  String Dado3;String Dado33;
  //====================================================================================
  void setup() 
  {
    ads.begin();
    Serial.begin(9600);
    
    // Print Message Of I/O Setting Progress
    Serial.println("\nI/O Pins Modes Set .... Done");

    // Starting To Connect
    if(WiFi.status() == WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      delay(50);
    }
    
    WiFi.mode(WIFI_STA);                // To Avoid Broadcasting An SSID
    WiFi.begin("FVMLearning", "");      // The SSID That We Want To Connect To

    // Printing Message For User That Connetion Is On Process
    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

    // WiFi Connectivity
    CheckWiFiConnectivity();        // Checking For Connection

    Serial.println("!-- Client Device Connected --!");

    // Printing IP Address
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
    Serial.print  ("Server IP Address : ");
    Serial.println(ESPServer);
    Serial.print  ("Server Port Num   : ");
    Serial.println(ESPServerPort);
    // Printing MAC Address
    Serial.print  ("Device MC Address : ");
    Serial.println(String(WiFi.macAddress()));
    // Printing IP Address
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
    
    // Conecting The Device As A Client
    ESPRequest();
  }
//====================================================================================
  void loop()
  {
  int16_t adc0, adc1, adc2, adc3;
  
  for (int i = 0; i <= 50; i++) {
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);
    Dado00 = String(adc0); 
    Dado11 = String(adc1); 
    Dado22 = String(adc2); 
    Dado33 = String(adc3);
    Dado0 += Dado00 + "|"; 
    Dado1 += Dado11 + "|"; 
    Dado2 += Dado22 + "|"; 
    Dado3 += Dado33 + "|";}
  
  Serial.println("DADOS");
  Serial.println(Dado0);
  Serial.println(Dado1);
  Serial.println(Dado2);
  Serial.println(Dado3);
  
  Serial.println   (ClientType + ";" + Dado0 + "-" + Dado1 + ":" + Dado2 + "/" + Dado3 + ">");
  ESPClient.println(ClientType + ";" + Dado0 + "-" + Dado1 + ":" + Dado2 + "/" + Dado3 + ">");

    Dado0 = "|"; 
    Dado1 = "|"; 
    Dado2 = "|"; 
    Dado3 = "|";
 
  ESPClient.flush();
  delay(500);
  }
//====================================================================================
 void CheckWiFiConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        delay(50);
        Serial.print(".");
      }
      Serial.println("");
    }
  }
  
  void ESPRequest()
  {
    // First Make Sure You Got Disconnected
    ESPClient.stop();

    // If Sucessfully Connected Send Connection Message
    if(ESPClient.connect(ESPServer, ESPServerPort))
    {
      Serial.println    ("<" + ClientType + "- CONNECTED>");
      ESPClient.println ("<" + ClientType + "- CONNECTED>");
    }
  }
