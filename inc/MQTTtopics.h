#ifndef MQTTTOPICS_DATA_H
#define MQTTTOPICS_DATA_H

constexpr const char* MQTT_TOPIC_ALL          = "/smarthome/*";
constexpr const char* MQTT_TOPIC_LED_SINGLE   = "/smarthome/ledSingle/";
constexpr const char* MQTT_TOPIC_LED_RGB      = "/smarthome/ledRGB/";
constexpr const char* MQTT_TOPIC_LCD          = "/smarthome/lcd/";
constexpr const char* MQTT_TOPIC_SOUND        = "/smarthome/sound/";
constexpr const char* MQTT_TOPIC_FAN          = "/smarthome/fan/";
constexpr const char* MQTT_TOPIC_DOOR         = "/smarthome/door/";
constexpr const char* MQTT_TOPIC_WINDOW       = "/smarthome/window/";
constexpr const char* MQTT_TOPIC_TEMP         = "/smarthome/temp/";
constexpr const char* MQTT_TOPIC_RFID         = "/smarthome/rfid/";
constexpr const char* MQTT_TOPIC_GAS          = "/smarthome/gas/";
constexpr const char* MQTT_TOPIC_BUTTON_LEFT  = "/smarthome/buttonLeft/";
constexpr const char* MQTT_TOPIC_BUTTON_RIGHT = "/smarthome/buttonRight/";
constexpr const char* MQTT_TOPIC_STEAM        = "/smarthome/steam/";
constexpr const char* MQTT_TOPIC_MOVEMENT     = "/smarthome/movement/";

constexpr const char* MQTT_TOPIC_UPDATE_APPENDIX = "update";

#endif