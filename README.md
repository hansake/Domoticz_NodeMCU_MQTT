# Domoticz_NodeMCU_MQTT
Examples how to connect NodeMCU/ESP8266 with sensors to Domoticz using MQTT.

NodeMCU_MQTT_DHT22/NodeMCU_MQTT_DHT22.ino reads temperature and humidity from a DHT22 sensor and sends the data to Domoticz using MQTT.

NodeMCU_MQTT_1-Wire_temp/NodeMCU_MQTT_temp.ino reads temperature from a 1-Wire sensor and sends the data to Domoticz using MQTT.

These examples are using Domoticz installed on a Raspberry Pi.
In addition to Domoticz a MQTT broker has to be installed.
The Mosquitto MQTT broker is installed on the same Raspberry Pi.
The installation is described here: https://mosquitto.org/

The appropriate Arduino NodeMCU board package and libraries has also to be installed.
