/* NodeMCU with 1-Wire interface and MQTT
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino, D4 on NodeMCU
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// WiFi configuration
const char* ssid = "your SSID";
const char* password = "your password";

// MQTT configuration
const char* mqtt_server = "your IP address";
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
const int idx1 = 286; /* must be the same as virual sensor idx in Domotocz */
const int idx2 = 287; /* must be the same as virual sensor idx in Domotocz */
char mqttbuffer[60];
float temperature1 = 0.0;
float temperature2 = 0.0;

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

  // Start up the 1-Wire library
  sensors.begin();
  Serial.println("1-Wire library started");

  // Start WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

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
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Read and publish temperature
  digitalWrite(led, led_on);
  sensors.requestTemperatures(); // Send the command to get temperatures
  temperature1 = sensors.getTempCByIndex(0);
  temperature2 = sensors.getTempCByIndex(1);
  sprintf(mqttbuffer, "{ \"idx\" : %d, \"nvalue\" : 0, \"svalue\" : \"%3.1f\" }", idx1, temperature1);
  // send temperature 1 to the MQTT topic
  client.publish(mqtt_topic, mqttbuffer);
  sprintf(mqttbuffer, "{ \"idx\" : %d, \"nvalue\" : 0, \"svalue\" : \"%3.1f\" }", idx2, temperature2);
  // send temperature 2 to the MQTT topic
  client.publish(mqtt_topic, mqttbuffer);
  digitalWrite(led, led_off);

  // Wait 5 seconds before reading temperature again
  delay(5000);
}
