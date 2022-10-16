#pragma once
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Consts.h"


class MqttController {
private:
    PubSubClient client;
public:
    MqttController(){
        WiFiClient espClient;
        this->client = PubSubClient(espClient);
    }
    void setup(std::function<void (char *, uint8_t *, unsigned int)> callback);
    void connect();
    void loop();
    void pingStatus();
    void publish(const char *topic, const char *payload);
};

void MqttController::loop() {
    client.loop();
    this->connect();
}

void MqttController::setup(std::function<void (char *, uint8_t *, unsigned int)> callback) {
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void MqttController::connect() {
  while (!client.connected()) {
    if (client.connect(mqtt_client.c_str(), mqtt_user, mqtt_pass)) {
      client.subscribe(SUB_TOPIC_TRAILER.c_str());
      client.subscribe(SUB_TOPIC_DOCUMENTS.c_str());
      client.subscribe(SUB_TOPIC_LIGHTS.c_str());
    }
  }
}

void MqttController::publish(const char *topic, const char *payload) {
  client.publish(topic, payload);
}
