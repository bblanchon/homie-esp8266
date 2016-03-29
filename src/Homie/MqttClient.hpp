#pragma once

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "Logger.hpp"
#include "Constants.hpp"
#include "Limits.hpp"

namespace HomieInternals {
  class MqttClientClass {
    public:
      MqttClientClass();
      ~MqttClientClass();

      void initMqtt(bool secure);
      char* getTopicBuffer();
      void setCallback(std::function<void(char* topic, char* message)> callback);
      void setServer(const char* host, unsigned int port, const char* fingerprint);
      bool connect(const char* clientId, const char* willMessage, unsigned char willQos, bool willRetain, bool auth = false, const char* username = nullptr, const char* password = nullptr);
      void disconnect();
      bool publish(const char* message, bool retained);
      bool subscribe(unsigned char qos);
      void loop();
      bool connected();

    private:
      WiFiClient _wifiClient;
      WiFiClientSecure _wifiClientSecure;
      PubSubClient _pubSubClient;
      char _topicBuffer[TOPIC_BUFFER_LENGTH];
      bool _secure;
      const char* _host;
      unsigned int _port;
      const char* _fingerprint;
      unsigned char _subscribeWithoutLoop;

      void _callback(char* topic, unsigned char* payload, unsigned int length);
      std::function<void(char* topic, char* message)> _userCallback;
  };

  extern MqttClientClass MqttClient;
}