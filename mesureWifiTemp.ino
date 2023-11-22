#include <WiFi.h> 
 
int DS18b20_Pin = 19; //Broche du capteur DS18b20 
byte addr[8] {0x28, 0xFF, 0x18, 0x29, 0x7, 0x0, 0x0, 0x93}; //Adresse du capteur DS18b20 sur le bus OneWire 
 
const char* ssid = "TP_BTS_SNIR_CIEL_2.4GHz"; 
const char* password = "mdpWIFI2.4"; 
 
// Set your Static IP address 
IPAddress local_IP(192, 168, 110, 17); 
// Set your Gateway IP address 
IPAddress gateway(192, 168, 110, 1); 
IPAddress subnet(255, 255, 0, 0); 
 
 
void initWiFi() { 
  WiFi.mode(WIFI_STA); 
  if (!WiFi.config(local_IP, gateway, subnet)) { 
  Serial.println("STA Failed to configure"); 
} 
  WiFi.begin(ssid, password); 
  Serial.print("Connecting to WiFi .."); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print('.'); 
    delay(1000); 
  } 
  Serial.println(WiFi.localIP()); 
} 
 
void setup() { 
  Serial.begin(115200); 
  initWiFi(); 
  Serial.print("RRSI: "); 
  Serial.println(WiFi.RSSI()); 
} 
 
void loop() { 
  Serial.println("scan start"); 
 
  // WiFi.scanNetworks will return the number of networks found 
  int n = WiFi.scanNetworks(); 
  Serial.println("scan done"); 
  if (n == 0) { 
      Serial.println("no networks found"); 
  } else { 
    Serial.print(n); 
    Serial.println(" networks found"); 
    for (int i = 0; i < n; ++i) { 
      // Print SSID and RSSI for each network found 
      Serial.print(i + 1); 
      Serial.print(": "); 
      Serial.print(WiFi.SSID(i)); 
      Serial.print(" ("); 
      Serial.print(WiFi.RSSI(i)); 
      Serial.print(")"); 
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*"); 
      delay(10); 
    } 
  } 
  Serial.println(""); 
 
  // Wait a bit before scanning again 
  delay(5000); 
}
