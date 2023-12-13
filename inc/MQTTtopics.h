#ifndef MQTTTOPICS_DATA_H
#define MQTTTOPICS_DATA_H

//get all topics:        "/smarthome/primaryhome/+/";
//get all topics update: "/smarthome/primaryhome/+/update";

constexpr const char MQTT_TOPIC_INIT[]         = "/smarthome/primaryhome/init/";
constexpr const char MQTT_TOPIC_LED_SINGLE[]   = "/smarthome/primaryhome/ledSingle/";
constexpr const char MQTT_TOPIC_LED_RGB[]      = "/smarthome/primaryhome/ledRGB/";
constexpr const char MQTT_TOPIC_LCD[]          = "/smarthome/primaryhome/lcd/";
constexpr const char MQTT_TOPIC_SOUND[]        = "/smarthome/primaryhome/sound/";
constexpr const char MQTT_TOPIC_FAN[]          = "/smarthome/primaryhome/fan/";
constexpr const char MQTT_TOPIC_DOOR[]         = "/smarthome/primaryhome/door/";
constexpr const char MQTT_TOPIC_WINDOW[]       = "/smarthome/primaryhome/window/";
constexpr const char MQTT_TOPIC_TEMP[]         = "/smarthome/primaryhome/temp/";
constexpr const char MQTT_TOPIC_RFID[]         = "/smarthome/primaryhome/rfid/";
constexpr const char MQTT_TOPIC_GAS[]          = "/smarthome/primaryhome/gas/";
constexpr const char MQTT_TOPIC_BUTTON_LEFT[]  = "/smarthome/primaryhome/buttonLeft/";
constexpr const char MQTT_TOPIC_BUTTON_RIGHT[] = "/smarthome/primaryhome/buttonRight/";
constexpr const char MQTT_TOPIC_STEAM[]        = "/smarthome/primaryhome/steam/";
constexpr const char MQTT_TOPIC_MOVEMENT[]     = "/smarthome/primaryhome/movement/";

constexpr const char* MQTT_TOPIC_UPDATE_APPENDIX = "update";

#endif