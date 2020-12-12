  #include <ESP8266WiFi.h>
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
  String Dado1;String Dado2;String Dado3;String Dado4;
  float Dado11;float Dado22;float Dado33;float Dado44;
  float TensaoNaBateria;
  void AvailableMessage()
  {
    //check clients for data
    for(uint8_t i = 0; i < MAXSC; i++)
    {
      if (ESPClient[i] && ESPClient[i].connected() && ESPClient[i].available())
      {
          while(ESPClient[i].available())
          {
            Message = ESPClient[i].readStringUntil('\r');
                     
            Dado1=Message.substring(Message.indexOf(";") + 1, Message.indexOf("-"));
            Dado11 = Dado1.toFloat();
            Dado2=Message.substring(Message.indexOf("-") + 1, Message.indexOf(":"));
            Dado22 = Dado2.toFloat();
            Dado3=Message.substring(Message.indexOf(":") + 1, Message.indexOf("/"));
            Dado33 = Dado3.toFloat();
            Dado4=Message.substring(Message.indexOf("/") + 1, Message.indexOf(">"));
            Dado44 = Dado4.toFloat();
            Serial.println(Dado11);
            Serial.println(Dado22);
            Serial.println(Dado33);
            Serial.println(Dado44);

            TensaoNaBateria = (Dado44*0.003);
            Serial.println("Valor de tensão");
            Serial.println(TensaoNaBateria);
            
            ESPClient[i].flush();         
            ClientNumber();
            Serial.println("Client No " + String(i+1) + " - " + Message); 
            Serial.println("============================================");
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
