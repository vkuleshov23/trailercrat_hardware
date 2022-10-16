#include <Arduino.h>
#include "DeviceController.h"

// struct led
// {
//   uint8_t pin;
//   String topic;
//   String pub_topic;
//   String dataON;
//   String dataOFF;
//   bool mode = false;

//   void light(String data) {
//     if (data.compareTo(dataON)) {
//       digitalWrite(pin, HIGH);
//     }
//     else if (data.compareTo(dataOFF)) {
//       digitalWrite(pin, LOW);
//     }
//   }
//   String getStatus() {
//     mode = !mode;
//     if(mode) {
//       return "$" + pub_topic + ":" + dataON + ";";
//     } else {
//       return "$" + pub_topic + ":" + dataOFF + ";";
//     }
  
//   }
// };

// RFID rfid;
// led led1;
// led led2;
// led led3;
// Timer ping_timer;
// String str_for_topic = "";
// String str_for_data = "";
// bool read_topic_flag = false;
// bool read_data_flag = false;

// bool connect = false;

// void ping();
// void readSerial();
// void compare_topics(String topic, String data);
// bool compare(const char* src, const char* dst);

DeviceController deviceController;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  // led1.pin = led_pin1;
  // pinMode(led_pin1, OUTPUT);
  // led1.topic = SUB_TOPIC_TRAILER;
  // led1.pub_topic = PUB_TOPIC_TRAILER;
  // led1.dataOFF = "CLOSE";
  // led1.dataON = "OPEN";

  // led2.pin = led_pin2;
  // pinMode(led_pin2, OUTPUT);
  // led2.topic = SUB_TOPIC_DOCUMENTS;
  // led2.pub_topic = PUB_TOPIC_DOCUMENTS;
  // led2.dataOFF = "CLOSE";
  // led2.dataON = "OPEN";

  // led3.pin = led_pin3;
  // pinMode(led_pin3, OUTPUT);
  // led3.topic = SUB_TOPIC_LIGHTS;
  // led3.pub_topic = PUB_TOPIC_LIGHTS;
  // led3.dataOFF = "OFF";
  // led3.dataON = "ON";

  // rfid.setup();

  // ping_timer.start(5000);
  deviceController.setup();
}

void loop() {
   deviceController.update();
  // rfid.try_read_uid();
  // readSerial();
  // ping();
}

// bool compare(const char* src, const char* dst) {
//     for(int i = 0; src[i] != '\0'; i++) {
//         if (src[i] != dst[i]) {
//             return false;
//         }
//     }
//     return true;
// }

// void readSerial() {
//   if (Serial3.available() > 0) {
//     char incomingByte = Serial3.read();

//     if (incomingByte == ':') {
//       read_topic_flag = false;
//       read_data_flag = true;
//       return;
//     }
//     if (incomingByte == '$') {
//       read_topic_flag = true;
//       read_data_flag = false;
//       return;
//     }
//     if (incomingByte == ';') {
//       read_topic_flag = false;
//       read_data_flag = false;
//       compare_topics(str_for_topic, str_for_data);
//       connect = true;
//       Serial.println(str_for_topic + "--" + str_for_data);
//       str_for_topic = "";
//       str_for_data = "";
//       return;
//     }
    
//     if (read_topic_flag) {
//       str_for_topic += incomingByte;
//     }
//     if (read_data_flag) {
//       str_for_data += incomingByte;
//     }
//   }
// }

// void compare_topics(String topic, String data) {
//   if (compare(topic.c_str(), led1.topic.c_str())) {
//     led1.light(data);
//   }
//   if (compare(topic.c_str(), led2.topic.c_str())) {
//     led2.light(data);
//   }
//   if (compare(topic.c_str(), led3.topic.c_str())) {
//     led3.light(data);
//   }
// }

// void ping() {
//   if (ping_timer == 0 && connect) {

//     Serial3.print(led1.getStatus().c_str());
//     Serial3.print(led2.getStatus().c_str());
//     Serial3.print(led3.getStatus().c_str());

//     ping_timer.start(5000);
//   }
// }
