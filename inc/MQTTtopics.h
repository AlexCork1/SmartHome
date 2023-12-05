#ifndef MQTTTOPICS_DATA_H
#define MQTTTOPICS_DATA_H
#include <Arduino.h>

const String MQTT_TOPIC_ALL        = "/smarthome/*";
const String MQTT_TOPIC_LED_SINGLE = "/smarthome/ledSingle/";
const String MQTT_TOPIC_LED_RGB    = "/smarthome/ledRGB/";
const String MQTT_TOPIC_LCD        = "/smarthome/lcd/";
const String MQTT_TOPIC_SOUND      = "/smarthome/sound/";
const String MQTT_TOPIC_FAN        = "/smarthome/fan/";

const String MQTT_TOPIC_UPDATE_APPENDIX = "update";

#endif