#include "ESP8266WiFi.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
const char* ssid = "Tuyet Lan ";
const char* password = "12305abc";

#define MQTT_PORT 1884
#define MQTT_BROKER "broker.emqx.io:8083/mqtt" 
#define QOS 1
WiFiClient espClient;
WebSocketsClient webSocket;
void setup() 
{
    Serial.begin(115200);
    Serial.setTimeout(5);
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
    }
    delay(100);
    webSocket.begin("192.168.1.235",8080,"/ws");
    webSocket.setReconnectInterval(5000);
}
String msg = "";
void loop() 
{
    webSocket.loop();
    msg = "";
    msg = Serial.readString();
    if(msg.length() > 0)
        webSocket.sendTXT(msg);
}
