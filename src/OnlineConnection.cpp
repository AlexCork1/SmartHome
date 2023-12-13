#include "../inc/OnlineConnection.h"
#include "../inc/Debug.h"

/*###########################################################################################################################################*/
/*
*
*     CONSTRUCTORS
*
*/
/*###########################################################################################################################################*/
OnlineConnection::OnlineConnection() : _espClient(), _client(_espClient)
{
}

void OnlineConnection::Init(
  const char* SSID,
  const char* password,
  const char* mqtt_server,
  const char* mqtt_username,
  const char* mqtt_password,
  void (*mqtt_callback)(char*, byte*, unsigned int),
  void (*mqtt_register_topics)()) 
{
    Debugln("OnlineConnection ::: Init");
    _ssid = SSID;
    _password = password;
    _mqtt_server = mqtt_server;
    _mqtt_username = mqtt_username;
    _mqtt_password = mqtt_password;
    _mqtt_callback = mqtt_callback;
    _mqtt_register_topics_function = mqtt_register_topics;
 
    WiFi_Connect();
    MQTT_Connect();
}

/*###########################################################################################################################################*/
/*
*
*     PUBLIC methods
*
*/
/*###########################################################################################################################################*/

/* Loop method to check for WiFi and MQTT connections and library loop. MUST be inside loop() function of main program */
void OnlineConnection::Loop(){
  if(WiFi.status() != WL_CONNECTED)
    WiFi_Reconnect();

  if(!_client.connected())
    MQTT_Reconnect();
    
  _client.loop();
}

/* Send message to MQTT server with specific topic */
void OnlineConnection::Publish(const char* topic, const char* message){
  Debug("Publish:\nTopic: "); Debugln(topic);
  Debug("Message: "); Debugln(message);
  _client.publish(topic, message);
}

/* We need to register each topic we wish to listent to */
void OnlineConnection::RegisterTopic(const char* topic){
  _client.subscribe(topic);
}

/*###########################################################################################################################################*/
/*
*
*     PRIVATE methods
*
*/
/*###########################################################################################################################################*/
/* Connect to access point */
void OnlineConnection::WiFi_Connect(){
  Debug("Connecting to "); 
  Debugln(_ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  //wait for WiFi to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Debug("-");
  }
  Debugln();

  Debug("WiFi connected to an IP address: ");
  Debugln(WiFi.localIP());
}
/*  Reconnect to access point */
void OnlineConnection::WiFi_Reconnect(){
  while(WiFi.status() != WL_CONNECTED){
    Debugln("Ponovna povezava na WiFi....");
    WiFi.disconnect();
    WiFi.reconnect();

    //wait up to 10 seconds to connection to reestablih
    int8_t secondCounter = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      secondCounter++;
      Debug(".");

      if (secondCounter >= 10)
      {
        Debugln("neuspesna");
        return;
      }
    }
  }
  Debugln("Successful");
}
/* Connect to mqtt server  */
void OnlineConnection::MQTT_Connect(){
  _client.setServer(_mqtt_server, 1883);
  _client.setCallback(_mqtt_callback);
}
/* Reconnect to mqtt server  */
void OnlineConnection::MQTT_Reconnect(){
  while (!_client.connected()) {
    Debug("Attempting to reconnect to MQTT server....");
    String clientId("SmartHouse-");
    clientId += String(random(0xffff), HEX);

    //try to connect with username and password
    if (_client.connect(clientId.c_str(), _mqtt_username, _mqtt_password)) {
      Debugln("successful");
      if (_mqtt_register_topics_function != NULL)
        _mqtt_register_topics_function();
    }
    else {
      Debugln("unsuccessful. Retry will happen in three seconds");
      delay(3000);
    }
  }
}
