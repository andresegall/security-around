
#include <WiFi.h>
#include <esp_now.h>
#define LED 2   
#define MinDB -75

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
   
//******************************************************************************************
  
  }
    void loop() 
   {
    ScanForSlave();
    WiFi.scanDelete();
   }


  
