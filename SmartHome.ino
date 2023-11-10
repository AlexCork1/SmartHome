#define DEBUG

#include "Debug.h"
#include "OnlineConnection.h"
#include "DevicesInclude.h"

//data for access point connection
const char* ssid = "";      //WiFi names
const char* password = "";	//WiFi password

//data for MQTT server connection
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_username = "smarthome_keyestudio";
const char* mqtt_password = "smarthome_password_keyestudio";

//function prototypes
void IRAM_ATTR ISR_GASSenzor();
void IRAM_ATTR ISR_ButtonLeft_Click();
void IRAM_ATTR ISR_ButtonRight_Click();

void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length);
OnlineConnection connectToServer(ssid, password, mqtt_server, mqtt_username, mqtt_password, MQTT_message_callback);

//variables
LEDSingle ledSingle;
LEDRGB ledRGB;
LCDdisplay lcdDisplay;
Sound sound;
Opening door("door", 13, 13);
Opening window("window", 5, 10);
Fan fan;
GasSensor gasSensor(ISR_GASSenzor);
Button buttonLeft("button_left", 16, ISR_ButtonLeft_Click);
Button buttonRight("button_right", 27, ISR_ButtonRight_Click);

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
  &buttonRight
};

//inicializacija
void setup()
{
  #ifdef DEBUG
  for (Device* device : list_of_devices)
    Debugln(device->MQTT_Get_topic() + " " + device->Get_Current_State());
  #endif
}

void loop()
{
  connectToServer.Loop();
}


//MQTT callback function
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length)
{
  String topicStr = String(topic);
  String message;
  for (uint32_t i = 0; i < length; i++) message += (char)messageByte[i];
  Debug(topicStr); Debug(" "); Debugln(message);

  //find correct device for recevied message
  for (Device* device : list_of_devices){
    if (device->MQTT_Get_topic() == String(topic)){
      device->MQTT_Message_Subscribe(message);
      break;
    }
  }
}



/*###########################################################################################################################################*/
/*
 *
 *     ISR routines
 *
 */
/*###########################################################################################################################################*/
void IRAM_ATTR ISR_GASSenzor() {
  gasSensor.Set_Alarm();
}
void IRAM_ATTR ISR_ButtonLeft_Click() {
  buttonLeft.Pressed();
}
void IRAM_ATTR ISR_ButtonRight_Click() {
  buttonRight.Pressed();
}