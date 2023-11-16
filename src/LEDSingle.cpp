#include "../inc/Debug.h"
#include "../inc/LEDSingle.h"

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
LEDSingle::LEDSingle(String topic, void (*mqtt_publish)(String, String)) : LED(topic, mqtt_publish){
  _led_state = 0;
  pinMode(SINGLE_LED_PIN, OUTPUT);
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/
/* return single LED state as String */
String LEDSingle::Get_Current_State(){
  return String(_led_state);
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void LEDSingle::MQTT_Message_Subscribe(String message){
  if (message == "On"){
    On();
    return;
  }

  if (message == "Off"){
    Off();
    return;
  }
    
  if (message == "Toggle"){
    Toggle();
    return;
  }
}
void LEDSingle::MQTT_Message_Publish(){
  //TODO
  //MQTT_publish(MQTT_Get_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
/* Turn the single LED on */
void LEDSingle::On(){
  _led_state = 1;
  digitalWrite(SINGLE_LED_PIN, HIGH);
}

/* Turn the single LED off */
void LEDSingle::Off(){
  _led_state = 0;
  digitalWrite(SINGLE_LED_PIN, LOW);
}

/* Toggle the state of the single LED */
void LEDSingle::Toggle(){
  if (_led_state == 0)
    On();
  else
    Off();
}