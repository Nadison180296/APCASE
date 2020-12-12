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
    // Setting The Serial Port
    Serial.begin(115200);           // Computer Communication

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
            ESPClient[i].flush();         
            ClientNumber();
            Serial.println("Client No " + String(i+1) + " - " + Message); 
          }
        }
      }
    }
    
 // =================================================================================
   
    void  ClientNumber(){
     
      if (Message == "<Cliente 01-1>"){             // Check clent number, 01 = client 1, and after trace, status 1 = on, 0 = off
             //digitalWrite(LED2, HIGH);
      } 
      }
  

//====================================================================================
