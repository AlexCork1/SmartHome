#include "../inc/Debug.h"
#include "../inc/Fan.h"

constexpr const char Fan::START_COMMAND[];
constexpr const char Fan::STOP_COMMAND[];

/*###########################################################################################################################################*/
/*
 *
 *     CONSTRUCTORS
 *
 */
/*###########################################################################################################################################*/
Fan::Fan(const char* topic) : Device(topic){
}

/*###########################################################################################################################################*/
/*
 *
 *     PUBLIC methods
 *
 */
/*###########################################################################################################################################*/
void Fan::Init(){
    pinMode(FAN_DIR1_PIN, OUTPUT);
    pinMode(FAN_DIR2_PIN, OUTPUT);
    // analog write for ESP32
    // https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html
    ledcSetup(CHANNEL_NUMBER, 1200, 8);
    ledcAttachPin(FAN_DIR1_PIN, CHANNEL_NUMBER);

    digitalWrite(FAN_DIR2_PIN, LOW);

    Stop();
}
const char* Fan::Get_Current_State()
{
    snprintf(jsonBuffer, JSON_BUFFER_SIZE, JSON_FORMAT, _runningState ? '1' : '0');
    return jsonBuffer;
}

/* callback function that will be called when message with MQTT_Get_topic() is received */
void Fan::MQTT_Message_Subscribe(const String& message)
{
    if (strcmp(message.c_str(), START_COMMAND) == 0) Start();
    else if (strcmp(message.c_str(), STOP_COMMAND) == 0) Stop();
}

/*###########################################################################################################################################*/
/*
 *
 *     PRIVATE methods
 *
 */
/*###########################################################################################################################################*/
void Fan::Start()
{   /* Start fan*/
    _runningState = true;
    ledcWrite(CHANNEL_NUMBER, FAN_ON);
}


void Fan::Stop()
{   /* Stop fan  */
    _runningState = false;
    ledcWrite(CHANNEL_NUMBER, 0);
}
