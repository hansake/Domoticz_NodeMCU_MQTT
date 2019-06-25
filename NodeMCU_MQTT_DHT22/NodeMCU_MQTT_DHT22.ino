/* NodeMCU with DHT22 interface and MQTT
 * Thermometer and Hygrometer
 * 
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;

// WiFi configuration
const char* ssid = "your SSID";
const char* password = "your password";

// MQTT configuration
const char* mqtt_server = "your MQTT broker IP address";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* mqtt_topic = "domoticz/in";

WiFiClient espClient;
PubSubClient client(espClient);

// LED definitions
const int led = LED_BUILTIN;
const int led_on = LOW;
const int led_off = HIGH;

// Temperature variables
const int idxdht = 321; /* must be the same as virual sensor idx in Domotocz */
char mqttbuffer[60];
float temperature = 0.0;
float humidity = 0.0;

// Handle recieved MQTT message, just print it
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Reconnect to MQTT broker
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("NodeMCUClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, led_off);
  Serial.begin(115200);
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Setup DHT library
  dht.setup(4, DHTesp::DHT22); // Connect DHT sensor to GPIO 04
  Serial.println("DHT library started");

  // Start WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connect to WiFi AP");

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    digitalWrite(led, led_on);
    delay(200);
    Serial.print(".");
    digitalWrite(led, led_off);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop(void)
{
  // Wait between measurements
  delay(10 * dht.getMinimumSamplingPeriod());

  // Reconnect if needed
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Read and publish temperature
  digitalWrite(led, led_on);


  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  sprintf(mqttbuffer, "{ \"idx\" : %d, \"nvalue\" : 0, \"svalue\" : \"%3.1f;%3.1f;0\" }", idxdht, temperature, humidity);
  // send temperature and humidity to the MQTT topic
  client.publish(mqtt_topic, mqttbuffer);
  // Debug message
  Serial.println(mqttbuffer);

  digitalWrite(led, led_off);
}
