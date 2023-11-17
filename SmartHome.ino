#include "inc/Debug.h"
#include "inc/OnlineConnection.h"
#include "inc/DevicesInclude.h"

/*
This file is not uploaded on github. You need to add it and fill it with following information:

  Data to connect to access point:
    - const char* ssid          ->  WiFi name
    - const char* password      ->	WiFi password

  Data to connect to MQTT server:
    - const char* mqtt_server   -> URL to MQTT broker
    - const char* mqtt_username -> MQTT broker username
    - const char* mqtt_password -> MQTT broker password
*/
#include "secrets.h"

//function prototypes
void IRAM_ATTR ISR_GASSensor();
void IRAM_ATTR ISR_ButtonLeft_Click();
void IRAM_ATTR ISR_ButtonRight_Click();
void IRAM_ATTR ISR_MovementSensor();

void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length);
void MQTT_message_publish(String topic, String message);
void MQTT_Register_Topics();

OnlineConnection connectToServer;

//variables
LEDSingle ledSingle("ledSingle", MQTT_message_publish);
LEDRGB ledRGB("ledRGB", MQTT_message_publish);
LCDdisplay lcdDisplay("lcd", MQTT_message_publish);
Sound sound("sound", MQTT_message_publish);
Opening door("door", 13, 13, MQTT_message_publish);
Opening window("window", 5, 10, MQTT_message_publish);
Fan fan("fan", MQTT_message_publish);
GasSensor gasSensor("gas", ISR_GASSensor, MQTT_message_publish);
Button buttonLeft("button_left", 16, ISR_ButtonLeft_Click, MQTT_message_publish);
Button buttonRight("button_right", 27, ISR_ButtonRight_Click, MQTT_message_publish);
SteamSensor steam("steam", MQTT_message_publish);
MovementSensor movement("movement", ISR_MovementSensor, MQTT_message_publish);
RFIDSensor rfid("rfid", MQTT_message_publish);
TempHumSensor tempHum("temphum", MQTT_message_publish);

Device* list_of_devices[] = {
  &ledSingle,
  &ledRGB,
  &lcdDisplay,
  &sound,
  &door,
  &window,
  &fan,
  &gasSensor,
  &buttonLeft,
  &buttonRight,
  &steam,
  &movement,
  &rfid,
  &tempHum
};


//inicializacija
void setup()
{ 
  Debug_Init();
  Debugln("done");

  connectToServer.Init(ssid, password, mqtt_server, mqtt_username, mqtt_password, MQTT_message_callback, MQTT_Register_Topics);

  Debugln("setup end");
}

void loop()
{
  connectToServer.Loop();
  delay(50);
}


//MQTT callback function
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length)
{
  String topicStr = String(topic);
  String message;
  for (uint32_t i = 0; i < length; i++) message += (char)messageByte[i];

  Debug(topicStr); Debug(" "); Debugln(message);

  //find correct device for recevied message
  for (auto device : list_of_devices){
    if (device->Get_MQTT_topic() == String(topic)){
      device->MQTT_Message_Subscribe(message);
      break;
    }
  }
}

//MQTT publish function
void MQTT_message_publish(String topic, String message)
{
  connectToServer.Publish(topic, message);
}

void MQTT_Register_Topics(){
  for(auto device : list_of_devices)
    connectToServer.RegisterTopic(device->Get_MQTT_topic());
}


/*###########################################################################################################################################*/
/*
 *
 *     ISR routines
 *
 */
/*###########################################################################################################################################*/

void IRAM_ATTR ISR_GASSensor() {
  //gasSensor.Set_Alarm();
}
void IRAM_ATTR ISR_ButtonLeft_Click() {
  //buttonLeft.Pressed();
}
void IRAM_ATTR ISR_ButtonRight_Click() {
  //buttonRight.Pressed();
}
void IRAM_ATTR ISR_MovementSensor() {
  //movement.Detected();
}