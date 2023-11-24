#ifndef MQTTTOPICS_DATA_H
#define MQTTTOPICS_DATA_H
#include <Arduino.h>

const String MQTT_TOPIC_PREFIX = "/smarthome/";
const String MQTT_TOPIC_GET_ALL = MQTT_TOPIC_PREFIX + "*";
const String MQTT_TOPIC_UPDATE = "/update";

#endif