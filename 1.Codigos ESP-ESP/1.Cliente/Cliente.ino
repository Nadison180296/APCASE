  #include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU

  const String  ClientType       = "Cliente 01";

  char*         ESPssid;            // Wifi Name
  char*         ESPpassword;        // Wifi Password

  int             ESPServerPort  = 9001;
  IPAddress       ESPServer(192,168,4,1);
  WiFiClient      ESPClient;
//====================================================================================

  void setup() 
  {
    // Setting The Serial Port ----------------------------------------------
    Serial.begin(9600);           // Computer Communication
    
    // Print Message Of I/O Setting Progress --------------------------------
    Serial.println("\nI/O Pins Modes Set .... Done");

    // Starting To Connect --------------------------------------------------
    if(WiFi.status() == WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      delay(50);
    }
    
    WiFi.mode(WIFI_STA);                // To Avoid Broadcasting An SSID
    WiFi.begin("FVMLearning", "");      // The SSID That We Want To Connect To

    // Printing Message For User That Connetion Is On Process ---------------
    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

    // WiFi Connectivity ----------------------------------------------------
    CheckWiFiConnectivity();        // Checking For Connection

    Serial.println("!-- Client Device Connected --!");

    // Printing IP Address --------------------------------------------------
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
    
    // Conecting The Device As A Client -------------------------------------
    ESPRequest();
  }

//====================================================================================
  int LEDState  = 0;
  void loop()
  {

    Serial.println   ("<" + ClientType + "-" + LEDState + ">");
    ESPClient.println("<" + ClientType + "-" + LEDState + ">");
    ESPClient.flush();
    delay(100);
    LEDState = LEDState +1;
  
  }

//====================================================================================
 void CheckWiFiConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        delay(500);
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
