#ifndef ONLINECONNECTION_DATA_H
#define ONLINECONNECTION_DATA_H

#include <WiFi.h>
#include <PubSubClient.h> //knjiznica: https://github.com/knolleary/pubsubclient

class OnlineConnection
{
  public:
    OnlineConnection(const char* ssid, const char* password, const char* mqtt_server, const char* mqtt_username, const char* mqtt_password, void (*mqttCallback)(char*, byte*, unsigned int));
    void Loop();
    void MQTT_Publish_Message(const char* topic, const char* message);

  private:
    WiFiClient _espClient; //used to connect to WiFi
    PubSubClient _client; //connect to MQTT server
    const char* _ssid;
    const char* _password;
    const char* _mqtt_server;
    const char* _mqtt_username;
    const char* _mqtt_password;
    void (*_mqtt_callback)(char*, byte*, unsigned int);

    void WiFi_Connect();
    void WiFi_Reconnect();

    void MQTT_Connect();
    void MQTT_Reconnect();
};


#endif