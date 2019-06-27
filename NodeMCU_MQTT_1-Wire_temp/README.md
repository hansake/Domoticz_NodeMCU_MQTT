Create two Dummy Virtual temperature sensors in Domoticz.

* Under Setup/Hardware add a device of type: "Dummy (Does nothing, use for virtual switches only)" with the name "Virtual Sensors".
* In the corresponding entry of your just created "Dummy" hardware, click the "Create Virtual Sensors" button that appear following the type. Then enter a device name and set Sensor Type: Temperature.
* Under Setup/Devices, get the "idx" number of your device which is 286 in this installation.
* Then click the "Create Virtual Sensors" button again. Enter a device name name and set Sensor Type: Temperature.
* Under Setup/Devices, get the "idx" number of your device which is 287 in this installation.

The following libraries should be added to the Arduino IDE to handle the 1-Wire interface with temperature sensors:
* Sketch in Adruino IDE -> Include Library -> Manage Libraries and select to install: OneWire
* Sketch in Adruino IDE -> Include Library -> Manage Libraries and select to install: MAX31850_DallasTemp
