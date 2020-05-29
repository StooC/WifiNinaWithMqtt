#include <Arduino.h>

#include <WiFiNINA.h>
#include <PubSubClient.h>

#include "secrets.h"

const char wifiSsid[] = WIFI_NAME; // WiFI ssid
const char wifiPassword[] = WIFI_PWD; //WiFI password
const char mqttUsername[] = MQTT_USERNAME; // broker key
const char mqttPassword[] = MQTT_PASSWORD; // broker secret
const char device[] = "pyportal"; // broker device identifier

/*
Methods
*/
void printConnectionInformation();
void callback(char* topic, byte* payload, unsigned int length);
void connect();

/* 
Globals
*/
int status = WL_IDLE_STATUS;
// Local MQTT Broker IP Address - to use hostname would need mDNS client
IPAddress server(192, 168, MQTT_BROKER_IP3, MQTT_BROKER_IP4);
WiFiClient net;
PubSubClient client(server, 1883, callback, net);

void setup() {
  Serial.begin(115200);
  connect();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  if (!client.connected()) {
    connect();
  }
  
  client.loop(); 
}

/*
Connects to Wifi and MQTT Broker
*/
void connect() {
  Serial.print("checking wifi...");
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(wifiSsid, wifiPassword);
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected to WiFi!\n");
  
  // Connection successful
  Serial.print("[INFO] Connection Successful");
  Serial.print("");  
  printConnectionInformation();
  Serial.println("-----------------------------------------------");
  Serial.println(""); 

  Serial.print("Attempting MQTT connection ....");
  if (client.connect(device, mqttUsername, mqttPassword)) {   
    Serial.println("Connected to MQTT Broker");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("try again in 5 second");
    digitalWrite(LED_BUILTIN, LOW);
    delay(5000);
  }

  client.setCallback(callback);
  client.subscribe("test/hello");
}

/*
Callback method for MQTT message received
*/ 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived --[");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/*
Prints Wifi connection information
*/
void printConnectionInformation() 
{
  // Print Network SSID
  Serial.print("[INFO] SSID: ");
  Serial.println(WiFi.SSID());

  // Print Router's MAC address
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("[INFO] BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // Print received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("[INFO] Signal Strength (RSSI): ");
  Serial.println(rssi);

  // Print encryption type
  byte encryption = WiFi.encryptionType();
  Serial.print("[INFO] Encryption Type: ");
  Serial.println(encryption, HEX);

  // Print WiFi Shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("[INFO] IP Address: ");
  Serial.println(ip);

  // Print MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("[INFO] MAC Address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}
