# SmartHome
## Overview
This project involves a <b>Keystudio SmartHome KS5009</b> device running on an ESP32. The device communicates with an Android app through an MQTT broker (HiveMQ).<br />

Link to Keystudio SmartHome KS5009: [Keystudio SmartHome KS5009](https://wiki.keyestudio.com/KS5009_Keyestudio_Smart_Home)

![Smart home image](https://github.com/AlexCork1/SmartHome/raw/main/SmartHomeImage.jpg)



## Getting Started
### Prerequisites
- Arduino IDE (for modifying ESP32 code)
- [Android App](https://github.com/AlexCork1/SmarthomeAndroidApp)
- HiveMQ MQTT broker (it is free to use, but the program can be modified to use another) (make changes in file secrets.h)
- WiFi access point (make changes in file secrets.h)

## Installation
Clone this repository to your local machine.
- Copy code (git clone [https://github.com/AlexCork1/SmartHome.git](https://github.com/AlexCork1/SmartHome.git))
- Open in Arduino IDE or VS Code
- Select Board: **ESP32 Dev Module**
- Select Port
- Upload the code

## Configuration
- Update the MQTT connection details in file **secrets.h**
- Update WiFi Access Point connection details  n file **secrets.h**

## Usage
Connect the Keystudio Smart Home KS5009 device to power.
Launch the Android app on your device.
Use the app to control and monitor the Smart Home device.

## License
This project is licensed under the [MIT]

## Acknowledgments
Here is a list of few libraries used in the project:
- [ArduinoJSON](https://arduinojson.org/)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [LiteLED](https://github.com/Xylopyrographer/LiteLED/tree/main)
- [pubsubclient](https://github.com/knolleary/pubsubclient)
- [MFRC522v2](https://github.com/OSSLibraries/Arduino_MFRC522v2)
- [Arduino songs](https://github.com/robsoncouto/arduino-songs/tree/master)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library/tree/master)
