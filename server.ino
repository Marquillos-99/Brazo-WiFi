
#include <WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 3
#define PORT  23
const char* ssid = "server";//Server
const char* pass = "robo2022";//1234

int valores[3] = {0,0,0};
WiFiServer server(PORT);
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();

  server.begin();
  server.setNoDelay(true);  

  Serial.print("SSID: ");           Serial.println(ssid);
  Serial.print("Password: ");       Serial.println(pass);  

  Serial.print("AP IP address: ");  Serial.println(myIP);
  Serial.print("Port: ");           Serial.println(PORT);
}

void loop() {
  uint8_t i;
  
  if (server.hasClient()) {
    Serial.println("entro al if de has client");    
    if (!serverClients[i] || !serverClients[i].connected()) {
      if (serverClients[i]) {
        serverClients[i].stop();
      } 
      Serial.println(server.available());
      serverClients[i] = server.available();
      Serial.println("New client: ");// Serial.println(i);
               
      Serial.print("Clients: ");
      Serial.println(serverClients[i]);
      Serial.print("Clients read: ");
      Serial.println(serverClients[i].read());
      
      for (int j=0; j <= 2; j++) {
        Serial.print("iterator: ");
        Serial.println(j);
        Serial.print("Punto read: ");                                      
        Serial.println(serverClients[i].read()); 
        valores[j]=serverClients[i].read();
        Serial.print("valores leidos: ");
        Serial.println(valores[j]);
        Serial.println("----------------------------------------------------");
      }     
    }
  }
 
}
