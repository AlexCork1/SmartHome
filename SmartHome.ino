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
#include <ESP32TimerInterrupt.h>

/*###############################################################################################################*/
/*
 *     function prototypes
 */
/*###############################################################################################################*/
void Publish(const char* topic, const char* message);
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length);
void MQTT_register_topics();
void IRAM_ATTR ISR_GASSensor();
void IRAM_ATTR ISR_ButtonLeft_Click();
void IRAM_ATTR ISR_ButtonRight_Click();
void IRAM_ATTR ISR_MovementSensor();
bool IRAM_ATTR TimerHandler0(void * timerNo);


/*###############################################################################################################*/
/*
 *     remote controled devices
 */
/*###############################################################################################################*/
LEDSingle ledSingle(MQTT_TOPIC_LED_SINGLE);
LEDRGB ledRGB(MQTT_TOPIC_LED_RGB);
LCDdisplay lcdDisplay(MQTT_TOPIC_LCD);
Sound sound(MQTT_TOPIC_SOUND, Publish);
Fan fan(MQTT_TOPIC_FAN);
Opening door(MQTT_TOPIC_DOOR, 13, 13);
Opening window(MQTT_TOPIC_WINDOW, 5, 10);

/*###############################################################################################################*/
/*
 *     ISR based devices
 */
/*###############################################################################################################*/
GasSensor gasSensor(MQTT_TOPIC_GAS, ISR_GASSensor);
Button buttonLeft(MQTT_TOPIC_BUTTON_LEFT, 16, ISR_ButtonLeft_Click);
Button buttonRight(MQTT_TOPIC_BUTTON_RIGHT, 27, ISR_ButtonRight_Click);
MovementSensor movement(MQTT_TOPIC_MOVEMENT, ISR_MovementSensor);
volatile bool gasSensorDetectedChange;
volatile bool buttonLeftDetectedChange;
volatile bool buttonRightDetectedChange;
volatile bool movementDetectedChange;

/*###############################################################################################################*/
/*
 *     periodic devices
 */
/*###############################################################################################################*/
RFIDSensor rfid(MQTT_TOPIC_RFID);
SteamSensor steam(MQTT_TOPIC_STEAM);
TempHumSensor tempHum(MQTT_TOPIC_TEMP);
volatile bool timerISR;


/*###############################################################################################################*/
/*
 *     private variables
 */
/*###############################################################################################################*/
OnlineConnection connectToServer;
constexpr int32_t TIMER0_INTERVAL_MS = 1000;
ESP32Timer ITimer0(0);

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
  &buttonLeft,
  &buttonRight,
  &steam,
  &movement
};


/*###############################################################################################################*/
/*
 *     methods
 */
/*###############################################################################################################*/
void Inits()
{
  connectToServer.Init(ssid, password, mqtt_server, mqtt_username, mqtt_password, MQTT_message_callback, MQTT_register_topics);
  lcdDisplay.Init();
  gasSensorDetectedChange = false;
  buttonLeftDetectedChange = false;
  buttonRightDetectedChange = false;

  // set timer 0 in microsecs
	if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
		Debug(F("Starting  ITimer0 OK, millis() = "));
    Debugln(millis());
  }
	else{
		Debugln(F("Can't set ITimer0. Select another Timer, freq. or timer"));
  }
  timerISR = false;
}

//MQTT callback function
void MQTT_message_callback(char* topic, byte* messageByte, unsigned int length)
{
  String message;
  for (uint32_t i = 0; i < length; i++)
    message += (char)messageByte[i];

  Debug(topic); Debug(" "); Debugln(message);


  //check if topic is to get all devices (usually done on client application start)
  if (strcmp(topic, MQTT_TOPIC_ALL) == 0)
  {
    Debugln("All topic demand");
    for (auto device : list_of_devices) 
      connectToServer.Publish(
        (device->Get_MQTT_topic() + String(MQTT_TOPIC_UPDATE_APPENDIX)).c_str(),
        device->Get_Current_State());
    return;
  }

  //find correct device for recevied message
  for (auto device : list_of_devices)
  {
    if (strcmp(device->Get_MQTT_topic(), topic) == 0)
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

void Publish(const char* topic, const char* message){
    connectToServer.Publish(
      (topic  + String(MQTT_TOPIC_UPDATE_APPENDIX)).c_str(),
      message);
}

void inline Process_RFID(){
  //check if any RFID card was detected
  String rfidPassword = rfid.ReadRFIDCard();
  if (rfidPassword.length() > 0)
    Publish(rfid.Get_MQTT_topic(), rfidPassword.c_str());
}
void inline Process_GASSensor(){
  //check if gas was detected
  if (gasSensorDetectedChange == true){
    Publish(gasSensor.Get_MQTT_topic(), gasSensor.Get_Current_State());
    gasSensorDetectedChange = false;
  }
}
void inline Process_LeftButton(){
  //check if left button was pressed
  if (buttonLeftDetectedChange == true){
    Publish(buttonLeft.Get_MQTT_topic(), buttonLeft.Get_Current_State());
    buttonLeftDetectedChange = false;
  }
}
void inline Process_RightButton(){
  //check if right button was pressed
  if (buttonRightDetectedChange == true){
    Publish(buttonRight.Get_MQTT_topic(), buttonRight.Get_Current_State());
    buttonRightDetectedChange = false;
  }
}
void inline Process_Movement(){
  //check if movement was detected
  if (movementDetectedChange == true){
    Publish(movement.Get_MQTT_topic(), movement.Get_Current_State());
    movementDetectedChange = false;
  }
}
void inline Process_TimerINT(){
  
  if(timerISR == true)
  {
    //check if steam sensor has a new value
    if (steam.Get_Data()) Publish(steam.Get_MQTT_topic(), steam.Get_Current_State());

    //check if temperaute sensor has a new value
    if (tempHum.Read_All()) Publish(tempHum.Get_MQTT_topic(), tempHum.Get_Current_State());

    timerISR = false;
  }
}

//SETUP function
void setup()
{ 
  Debug_Init(); Debugln("debug init done");

  Inits();

  Debugln("setup end");
}

//MAIN LOOP function
void loop()
{
  connectToServer.Loop();

  Process_RFID();
  Process_GASSensor();
  Process_LeftButton();
  Process_RightButton();
  Process_Movement();
  Process_TimerINT();

  delay(50);
}

/*###############################################################################################################*/
/*
 *     ISR routines
 */
/*###############################################################################################################*/
void IRAM_ATTR ISR_GASSensor() {
  if (gasSensor.Read_State() == HIGH)
    gasSensor.Set_Alarm();
  else
    gasSensor.Reset_Alarm();

  gasSensorDetectedChange = true;
}
void IRAM_ATTR ISR_ButtonLeft_Click() {
  if (buttonLeft.Read_State() == HIGH)
    buttonLeft.Pressed();
  else
    buttonLeft.Reset();
  
  buttonLeftDetectedChange = true;
}
void IRAM_ATTR ISR_ButtonRight_Click() {
  if (buttonRight.Read_State() == HIGH)
    buttonRight.Pressed();
  else
    buttonRight.Reset();
  
  buttonRightDetectedChange = true;
}
void IRAM_ATTR ISR_MovementSensor() {
  if (movement.Read_State() == HIGH)
    movement.Detected();
  else
    movement.Reset();
  
  movementDetectedChange = true;
}
bool IRAM_ATTR TimerHandler0(void * timerNo)
{
  timerISR = true;
	return true;
}