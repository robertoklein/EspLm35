#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* mqttServer = "m14.cloudmqtt.com";
const int mqttPort = 19616;
const char* mqttUser = "axxfrycf";
const char* mqttPassword = "qAdD5bpKyIk4";

WiFiClient espClient;
PubSubClient client(espClient);

int outputpin = A0;

char ssid[] = "AndroidAP";
char pass[] = "ifyy0846";

void setup() {
Serial.begin(9600);
WiFi.begin(ssid,pass);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.println("Connecting to WiFi..");
}

client.setServer(mqttServer, mqttPort);
//client.setCallback(callback);

while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

Serial.println("Connected to the WiFi network");
}

void loop() {
  int analogValue = analogRead(outputpin);
  float millivolts = (analogValue/1024.0) * 3300;
  float celsius = millivolts/10;
  Serial.print("in DegreeC= ");
  Serial.println(celsius);
  client.loop();
  client.publish("roberto", String (celsius).c_str());
  delay(5000);
}
