#include <Arduino.h>
#include "MqttController.h"
#include "Consts.h"
#include "Timer.h"
#include <ESP8266WiFi.h>

MqttController mqttController;
DynamicJsonDocument received_data = DynamicJsonDocument(256);
Timer timer = Timer();
bool brightness = true;

String str_for_topic = "";
String str_for_data = "";
bool read_topic_flag = false;
bool read_data_flag = false;


void receivedCallback(char* topic, byte* payload, unsigned int length);
bool compare(const char* src, char* dst);
void readSerial();
void send(String topic, String data);

void setup() {
  Serial.begin(9600);
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  mqttController.setup(receivedCallback);
}

void loop() {
  mqttController.loop();
  readSerial();
}

void receivedCallback(char* topic, byte* payload, unsigned int length) {
    deserializeJson(received_data, payload);
    const char* rec_status = received_data["status"];
    Serial.printf("$%s:%s;", topic, rec_status);
}

void readSerial() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();

    if (incomingByte == ':') {
      read_topic_flag = false;
      read_data_flag = true;
      return;
    }
    if (incomingByte == '$') {
      read_topic_flag = true;
      read_data_flag = false;
      return;
    }
    if (incomingByte == ';') {
      send(str_for_topic, str_for_data);
      read_topic_flag = false;
      read_data_flag = false;
      str_for_topic = "";
      str_for_data = "";
      return;
    }
    
    if (read_topic_flag) {
      str_for_topic += incomingByte;
    }
    if (read_data_flag) {
      str_for_data += incomingByte;
    }
  }
}

void send(String topic, String data) {
  mqttController.publish(topic.c_str(), data.c_str());
}