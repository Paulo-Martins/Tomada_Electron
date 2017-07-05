/* ESP8266 Webserver for turning a 230V Bulb on and off.

   Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)
   and on DHTServer - ESP8266 Webserver with a DHT sensor as an input
   Version 1.0  5/3/2014  Version 1.0  from  Mike Barela for Adafruit Industries

   Version 0.6 04/07/2017 from Paulo-Martins @akanerd.com
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char* ssid     = "mynet"; // SSID da rede
const char* password = "12345"; // Utilizar a pass da rede

ESP8266WebServer server(80);



String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time

IPAddress staticIP(192, 168, 1, 99); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network


void handle_root() {
  server.send(200, "text/plain", "Hello from Tomada Server, Ligar/Desligar a partir de /on ou /off ");
  delay(100);
}

void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
           // initialize temperature sensor
  pinMode(D6, OUTPUT);
  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.hostname("ESP_Tomada");      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, gateway, subnet);  // (DNS not required)
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Tomada Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);



  server.on("/on", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    digitalWrite(D6, LOW);
    webString="Ligado: " ;
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });


  server.on("/off", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    digitalWrite(D6, HIGH);
    webString="Desligado " ;
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}
