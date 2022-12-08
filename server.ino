
#include <WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 3
#define PORT  23
const char* ssid = "server";//Server
const char* pass = "robo2022";//1234

int teta1, teta2, teta3;
int valores[3];
int teta[3];
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
  Serial.print("i fuera: ");
  Serial.println(i);  
  //check if there are any new clients
  if (server.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      //find free/disconnected spot
      Serial.print("MAX CLIENTS: ");
      Serial.println(MAX_SRV_CLIENTS); 
      Serial.print("i dentro: ");
      Serial.println(i);       
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (serverClients[i]) {
          serverClients[i].stop();
        }
        serverClients[i] = server.available();
        Serial.println("New client: ");// Serial.println(i);
        break;
      }
    }
    //no free/disconnected spot so reject
    if (i == MAX_SRV_CLIENTS) {
      WiFiClient serverClient = server.available();
      serverClient.stop();
      Serial.println("Connection rejected ");
    }
  }
  //check clients for data
 
  if (serverClients[1].available() && serverClients[1].connected()) {
        //get data from the telnet client and push it to the UART
    for (int j=0; j <= 2; j++) {
      Serial.print("iterator: ");
      Serial.println(j);
      Serial.print("Punto read: ");                                      
      Serial.println(serverClients[1].read()); 
      valores[j]=serverClients[1].read();
      Serial.print("valores leidos: ");
      Serial.println(valores[j]);
      Serial.println("----------------------------------------------------");
    }
  }
  //check UART for da ta
  // if (Serial.available()) {
  //   size_t len = Serial.available();
  //   uint8_t sbuf[len];
  //   Serial.readBytes(sbuf, len);
  //   //push UART data to all connected telnet clients
  //   for (i = 0; i < MAX_SRV_CLIENTS; i++) {
  //     if (serverClients[i] && serverClients[i].connected()) {
  //       serverClients[i].write(sbuf, len);
  //       delay(1);
  //     }
  //   }
  // }
}
