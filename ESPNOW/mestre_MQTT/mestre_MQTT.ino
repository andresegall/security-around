#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>
#include <esp_now.h>
#define LED 2   
#define MinDB -50
//**********************************************************************************
#define WLAN_SSID   "MDKAUT"
#define WLAN_PASS   "topdez@10"

//MQTT broker settings https://proyectoinfo.mybluemix.net
#define HOST        "10.0.0.121"
//#define HOST        "https://proyectoinfo.mybluemix.net/red"
#define PORT        1883
#define USERNAME    "teste"
#define PASSWORD    "1234"

//time out loop count
const int timeout = 200;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, HOST, PORT, USERNAME, PASSWORD);
Adafruit_MQTT_Publish acesso = Adafruit_MQTT_Publish(&mqtt, "acesso");

void MQTT_connect();
//********************************************************************************************
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 1 second...");
       mqtt.disconnect();
       delay(1000);
       retries--;
       if (retries == 0)
         Serial.println("No Conectado");
  }
  Serial.println("MQTT Connected!");
}

//**************************************************************************
void ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  int i=0;
  while(i<scanResults)
  //for( int i = 0 ; i<scanResults; ++ i)
  {
      
      String SSID = WiFi. SSID (i);
      int32_t RSSI = WiFi. RSSI (i);
      String BSSIDstr = WiFi. BSSIDstr (i);
       //Serial.print(SSID); Serial.print(" ");Serial.print(RSSI);Serial.print(" ");Serial.print(BSSIDstr);Serial.println("");
      // if (SSID=="NOW" && BSSIDstr == "58:D9:C3:43:E8:AC")
      if ((SSID=="NOW" && BSSIDstr == "42:F5:20:27:3A:8B")&&(RSSI>MinDB))
     {
     Serial.print(SSID); Serial.print(" ");Serial.print(RSSI);Serial.print(" ");Serial.print(BSSIDstr);Serial.print("");Serial.println(" INSEGURO");
      //if(RSSI>MinDB)
        //{   
         digitalWrite(LED, HIGH);  
         //WiFi.scanDelete();         
        }

        if ((SSID=="NOW" && BSSIDstr == "42:F5:20:27:3A:8B")&&(RSSI<MinDB))
      //else 
        {
          Serial.print(SSID); Serial.print(" ");Serial.print(RSSI);Serial.print(" ");Serial.print(BSSIDstr);Serial.print("");Serial.println(" SEGURO");
          digitalWrite(LED, LOW);
          //WiFi.scanDelete();
        }    
    // } 
     i++;
  }
  
 //WiFi.scanDelete();
}
//*******************************************************************************
void setup() 
  {
   Serial.begin(115200);
   pinMode(LED, OUTPUT);  
   WiFi.mode(WIFI_STA);

   //**************************************************************************
    Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
   WiFi.begin(WLAN_SSID, WLAN_PASS);
  int i = 0;
  for (; i < timeout; i++)
  {
    if(WiFi.status() == WL_CONNECTED) break;
    delay(100);
    Serial.print(".");
  }
  if(i == timeout)
    Serial.println("No Conectado");

  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  MQTT_connect();
//******************************************************************************************
  
  }
    void loop() 
   {
    MQTT_connect();
    ScanForSlave();
     WiFi.scanDelete();
     acesso.publish("5");
     
   }


  
