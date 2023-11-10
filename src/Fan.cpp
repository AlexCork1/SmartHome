#include "../inc/Debug.h"
#include "../inc/Fan.h"

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Fan::Fan()
{
    pinMode(FAN_DIR1_PIN, OUTPUT);
    pinMode(FAN_DIR2_PIN, OUTPUT);

    // analog write for ESP32
    // https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html
    ledcSetup(CHANNEL_NUMBER, 1200, 8);
    ledcAttachPin(FAN_DIR1_PIN, CHANNEL_NUMBER);

    digitalWrite(FAN_DIR2_PIN, LOW);

    Stop();
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
/* return single LED state as String */
String Fan::Get_Current_State()
{
    return String(_running_state);
}
/* return single LED MQTT topic as String */
String Fan::MQTT_Get_topic()
{
    return "fan";
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Fan::MQTT_Message_Subscribe(String message)
{
    if (message == "start")
        Start();
    else if (message == "stop")
        Stop();
}
void Fan::MQTT_Message_Publish()
{
    // TODO
    // MQTT_publish(MQTT_Get_topic().c_str(), GetData().c_str());
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
/* Start fan*/
void Fan::Start()
{
    _running_state = true;
    ledcWrite(CHANNEL_NUMBER, FAN_ON);
}

/* stop fan  */
void Fan::Stop()
{
    _running_state = false;
    ledcWrite(CHANNEL_NUMBER, 0);
}
