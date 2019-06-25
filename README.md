# Domoticz_NodeMCU_MQTT
Examples how to connect NodeMCU/ESP8266 with sensors to Domoticz using MQTT.

NodeMCU_MQTT_DHT22/NodeMCU_MQTT_DHT22.ino reads temperature and humidity from a DHT22 sensor and sends the data to Domoticz using MQTT.

NodeMCU_MQTT_1-Wire_temp/NodeMCU_MQTT_temp.ino reads temperature from a 1-Wire sensor and sends the data to Domoticz using MQTT.

These examples are using Domoticz installed on a Raspberry Pi.
In addition to Domoticz a MQTT broker has to be installed.
The Mosquitto MQTT broker is installed on the same Raspberry Pi.
The installation is described in the download section of https://mosquitto.org/

Domoticz needs to subscribe to the Mosquitto MQTT message broker that is now running locally. Under Setup/Hardware add a device:
* MQTT Client
* Type: "MQTT Client Gateway with LAN interface" with settings:
* Data Timeout: Disabled
* Remote Address: The IP address of the MQTT broker
* Port: 1883
* Username: empty
* Password: empty
* Publish Topic: out (not used here)
* CA Filename: empty (not used here?)
To finish press 'Add'.

To create the sketch for the NodeMCU the appropriate Arduino NodeMCU board package and libraries has also to be installed.
Common for both examples above:
* Sketch in Adruino IDE -> Tools -> Board -> Boards Manager to download "esp8266 by ESP 8266 Community"
* Sketch in Adruino IDE -> Tools -> Board and select NodeMCU 1.0 (We have NodeMCU v2, but we select as 1.0. Focus on inside of paranthesis ESP-12E is more important than this)
* Sketch in Adruino IDE -> Include Library -> Manage Libraries and select to install PubSubClient
