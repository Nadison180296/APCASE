#include "WiFiServer.h"
  char*       ESPssid;              // SERVER WIFI NAME
  char*       ESPpassword;          // SERVER PASSWORD
  String      Message;              // VARIABLE RECEIVE DATA FROM OTHER CLIENTS

  #define     MAXSC     6           // MAXIMUM NUMBER OF CLIENTS
  
  WiFiServer  ESPServer(9001);      // THE SERVER AND THE PORT NUMBER
  WiFiClient  ESPClient[MAXSC];     // THE SERVER CLIENTS (Devices)
//====================================================================================
  void setup()
  {
    Serial.begin(115200);

    Serial.println();
    Serial.println("I/O Pins Modes Set .... Done");

    // Setting Up A Wifi Access Point
    SetWifi("FVMLearning", "");
  }
//====================================================================================
  void loop()
  {    
    AvailableClients();     // Checking For Available Clients
    AvailableMessage();     // Checking For Available Client Messages
  }
//====================================================================================
  void SetWifi(char* Name, char* Password)
  {
    // Stop Any Previous WIFI
    WiFi.disconnect();

    // Setting The Wifi Mode
    WiFi.mode(WIFI_AP_STA);
    Serial.println("WIFI Mode : AccessPoint Station");
    
    // Setting The AccessPoint Name & Password
    ESPssid      = Name;
    ESPpassword  = Password;
    
    // Starting The Access Point
    WiFi.softAP(ESPssid, ESPpassword);
    Serial.println("WIFI < " + String(ESPssid) + " > ... Started");
    
    // Wait For Few Seconds
    delay(500);
    
    // Getting Server IP
    IPAddress IP = WiFi.softAPIP();
    
    // Printing The Server IP Address
    Serial.print("AccessPoint IP : ");
    Serial.println(IP);

    // Printing MAC Address
    Serial.print("AccessPoint MC : ");
    Serial.println(String(WiFi.softAPmacAddress()));

    // Starting Server
    ESPServer.begin();
    ESPServer.setNoDelay(true);
    Serial.println("Server Started");
  }
//====================================================================================
  void AvailableClients()
  {   
    if (ESPServer.hasClient())
    {
      for(uint8_t i = 0; i < MAXSC; i++)
      {
        //find free/disconnected spot
        if (!ESPClient[i] || !ESPClient[i].connected())
        {
          // Checks If Previously The Client Is Taken
          if(ESPClient[i])
          {
            ESPClient[i].stop();
          }

          // Checks If Clients Connected To The Server
          if(ESPClient[i] = ESPServer.available())
          {
            Serial.println("New Client: " + String(i+1));
          }

          // Continue Scanning
          continue;
        }
      }
      
      //no free/disconnected spot so reject
      WiFiClient ESPClient = ESPServer.available();
      ESPClient.stop();
    }
  }
//====================================================================================
  String Dado0;       String Dado1;       String Dado2;       String Dado3;
  String Dad0;        String Dad1;        String Dad2;        String Dad3;
  //float Dado00[200];  float Dado11[200];  float Dado22[200];  float Dado33[200];
  int Dado00[200];    int Dado11[200];    int Dado22[200];    int Dado33[200];
  float MT=0;
  float TensaoNaBateria;
  void AvailableMessage()
  {
    //check clients for data
    for(uint8_t i = 0; i < MAXSC; i++)
    {
                    Serial.print(" MAXSC= ");
              Serial.println( MAXSC);
      if (ESPClient[i] && ESPClient[i].connected() && ESPClient[i].available())
      {
          while(ESPClient[i].available())
          {
            Message = ESPClient[i].readStringUntil('\r');
                     
            Dado0=Message.substring(Message.indexOf(";") + 1, Message.indexOf("-"));
            //Dado00 = Dado1.toFloat();
            Dado1=Message.substring(Message.indexOf("-") + 1, Message.indexOf(":"));
            //Dado11 = Dado2.toFloat();
            Dado2=Message.substring(Message.indexOf(":") + 1, Message.indexOf("/"));
            //Dado22 = Dado3.toFloat();
            Dado3=Message.substring(Message.indexOf("/") + 1, Message.indexOf(">"));
            //Dado33 = Dado4.toFloat();
            int aux0=0;   int aux1=0;   int aux2=0;   int aux3=0;
            for (int j = 0; j <= 600; j++){
              if ( Dado0[j] == '|'){
                aux0=aux0+1;
                Dado00[aux0]=Dad0.toFloat();
                Dad0="";
              }else{
                Dad0 += Dado0[j];
              }

            if ( Dado1[j] == '|'){
                aux1=aux1+1;
                Dado11[aux1]=Dad1.toFloat();
                Dad1="";
              }else{
                Dad1 += Dado1[j];
              }

              if ( Dado2[j] == '|'){
                aux2=aux2+1;
                Dado22[aux2]=Dad2.toFloat();
                Dad2="";
              }else{
                Dad2 += Dado2[j];
              }

              if ( Dado3[j] == '|'){
                aux3=aux3+1;
                Dado33[aux3]=Dad3.toFloat();
                MT=(MT+Dado33[aux3])/2;
                Dad3="";
              }else{
                Dad3 += Dado3[j];
              }             
            }

              Serial.print("D0= ");
              Serial.println(Dado0);
              Serial.print("D1= ");
              Serial.println(Dado1);
              Serial.print("D2= ");
              Serial.println(Dado2);
              Serial.print("D3= ");
              Serial.println(Dado3);

            TensaoNaBateria = (MT*0.003);
            MT=0;
            Serial.println("Valor de tensão");
            Serial.println(TensaoNaBateria);
             ESPClient[i].flush();         
            ClientNumber();
            Serial.println("Client No " + String(i+1) + " - " + Message); 
            
            
            Serial.print("D0= ");
            for (int aux = 2; aux <= aux0; aux++){
              Serial.print("|");
              Serial.print(Dado00[aux]);
            }
            Serial.println("");
            Serial.print("D1= ");
            for (int aux = 2; aux <= aux1; aux++){
              Serial.print("|");
              Serial.print(Dado11[aux]);
            }
            Serial.println("");
            Serial.print("D2= ");
            for (int aux = 2; aux <= aux2; aux++){
              Serial.print("|");
              Serial.print(Dado22[aux]);
            }
            Serial.println("");
            Serial.print("D3= ");
            for (int aux = 2; aux <= aux3; aux++){
              Serial.print("|");
              Serial.print(Dado33[aux]);
            }
            Serial.println("");
            Serial.println("============================================");
            Serial.println("");
          }
        }
      }
    }
    
 // =================================================================================
   
    void  ClientNumber(){
     
      if (Message == "<Cliente-1>"){             // Check clent number, 01 = client 1, and after trace, status 1 = on, 0 = off
             //digitalWrite(LED2, HIGH);
             //Serial.println(Dados);
      }}
//====================================================================================
