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
void Publish(String topic, String message);
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length);
void MQTT_register_topics();

void IRAM_ATTR ISR_GASSensor();
void IRAM_ATTR ISR_ButtonLeft_Click();
void IRAM_ATTR ISR_ButtonRight_Click();
void IRAM_ATTR ISR_MovementSensor();


OnlineConnection connectToServer;

//variables
LEDSingle ledSingle(MQTT_TOPIC_LED_SINGLE);
LEDRGB ledRGB(MQTT_TOPIC_LED_RGB);
LCDdisplay lcdDisplay(MQTT_TOPIC_LCD);
Sound sound(MQTT_TOPIC_SOUND, Publish);
Fan fan(MQTT_TOPIC_FAN);
Opening door(MQTT_TOPIC_DOOR, 13, 13);
Opening window(MQTT_TOPIC_WINDOW, 5, 10);
TempHumSensor tempHum(MQTT_TOPIC_TEMP);
RFIDSensor rfid(MQTT_TOPIC_RFID);
GasSensor gasSensor(MQTT_TOPIC_GAS, ISR_GASSensor);
volatile bool gasSensorDetectedChange;

/*
Button buttonLeft("button_left", 16, ISR_ButtonLeft_Click, MQTT_message_publish);
Button buttonRight("button_right", 27, ISR_ButtonRight_Click, MQTT_message_publish);
SteamSensor steam("steam", MQTT_message_publish);
MovementSensor movement("movement", ISR_MovementSensor, MQTT_message_publish);
*/

Device* list_of_devices[] = {
  &ledSingle,
  &ledRGB,
  &lcdDisplay,
  &sound,
  &fan,
  &door,
  &window,
  &tempHum,
  &rfid,
  &gasSensor,
  /*
  &buttonLeft,
  &buttonRight,
  &steam,
  &movement,*/
};

void Inits()
{
  connectToServer.Init(ssid, password, mqtt_server, mqtt_username, mqtt_password, MQTT_message_callback, MQTT_register_topics);
  lcdDisplay.Init();
  gasSensorDetectedChange = false;
}

//inicializacija
void setup()
{ 
  Debug_Init();
  Debugln("done");

  Inits();

  Debugln("setup end");
}

void loop()
{
  connectToServer.Loop();

  //check if any RFID card was detected
  String rfidPassword = rfid.Read();
  if (rfidPassword.length() > 0) Publish(rfid.Get_MQTT_topic(), std::move(rfidPassword));

  //check if gas was detected
  if (gasSensorDetectedChange == true){
    Publish(gasSensor.Get_MQTT_topic(), gasSensor.Get_Current_State());
    gasSensorDetectedChange = false;
  }
  
  delay(50);
}


//MQTT callback function
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length)
{
  String topicStr = String(topic);
  String message;
  for (uint32_t i = 0; i < length; i++) message += (char)messageByte[i];

  Debug(topicStr); Debug(" "); Debugln(message);


  //check if topic is to get all devices (usually done on client application start)
  if (topicStr == MQTT_TOPIC_ALL)
  {
    Debugln("All topic demand");
    for (auto device : list_of_devices) 
      connectToServer.Publish(device->Get_MQTT_topic() + MQTT_TOPIC_UPDATE_APPENDIX, device->Get_Current_State());
    return;
  }

  //find correct device for recevied message
  for (auto device : list_of_devices)
  {
    if (device->Get_MQTT_topic() == String(topic))
    {
      //process incoming message for this device
      device->MQTT_Message_Subscribe(message);
      
      //broadcast new state to anyone listening
      Publish(device->Get_MQTT_topic(), device->Get_Current_State());

      break; //we assume only one device has the same topic
    }
  }
}

//MQTT publish function
void MQTT_register_topics(){
  connectToServer.RegisterTopic(MQTT_TOPIC_ALL);
  for(auto device : list_of_devices)
    connectToServer.RegisterTopic(device->Get_MQTT_topic());
}

void Publish(String topic, String message){
    connectToServer.Publish(topic  + MQTT_TOPIC_UPDATE_APPENDIX, message);
}
/*###########################################################################################################################################*/
/*
 *
 *     ISR routines
 *
 */
/*###########################################################################################################################################*/

void IRAM_ATTR ISR_GASSensor() {
  if (gasSensor.ReadState() == HIGH)
    gasSensor.Set_Alarm();
  else
    gasSensor.Reset_Alarm();

  gasSensorDetectedChange = true;
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