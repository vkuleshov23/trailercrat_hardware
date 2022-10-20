#include "StatusController.h"
#include "RelayController.h"
#include "RFID.h"

class DeviceController {
private:
    Timer ping_timer = Timer();
    StatusController statusController;
    RelayController relayController;
    void readSerial();
    String str_for_topic = "";
    String str_for_data = "";
    bool read_topic_flag = false;
    bool read_data_flag = false;
    bool connect = false;
public:
    void receivedCallback(String topic, String payload);
    void setup();
    void update();
    void pingStatus();
    void handleTrailer(const char* rec_status);
    void handleDocuments(const char* rec_status);
    void handleLights(const char* rec_status);
    bool compare(const char* src, const char* dst);
    void publish(String topic, String payload);
};

void DeviceController::update() {
    this->statusController.readData();
    this->relayController.update(this->statusController.isDockumentsInside());
    if (this->statusController.documentStatusWasUpdated()) ping_timer.start(0);
    this->readSerial();
    this->pingStatus();
}

void DeviceController::setup() {
    this->statusController.setup();
    this->relayController.setup();
}

void DeviceController::receivedCallback(String topic, String payload) {
    const char* rec_status = payload.c_str();
    Serial.println(topic);
    Serial.println(rec_status);

  if (compare(SUB_TOPIC_LIGHTS.c_str(), topic.c_str())) {
    handleLights(rec_status);
  }
  if(compare(SUB_TOPIC_DOCUMENTS.c_str(), topic.c_str())) {
    handleDocuments(rec_status);
    this->publish(PUB_TOPIC_DOCUMENTS.c_str(), statusController.getDocumentsStatus());
  } 
  if(compare(SUB_TOPIC_TRAILER.c_str(), topic.c_str())) {
    //--------------------------
    handleDocuments(rec_status);
    //--------------------------
    this->handleTrailer(rec_status);
    this->publish(PUB_TOPIC_TRAILER.c_str(), statusController.getTrailerStatus());
  }
}

void DeviceController::readSerial() {
  if (Serial3.available() > 0) {
    char incomingByte = Serial3.read();

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
      read_topic_flag = false;
      read_data_flag = false;
      this->receivedCallback(str_for_topic, str_for_data);
      connect = true;
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

void DeviceController::publish(String topic, String payload) {
    Serial3.print("$");
    Serial3.print(topic);
    Serial3.print(":");
    Serial3.print(payload);
    Serial3.print(";");
}

void DeviceController::handleLights(const char* rec_status) {
  this->relayController.handleLights((char*)rec_status, this->statusController.isDockumentsInside());
}

void DeviceController::handleTrailer(const char* rec_status) {
  if(this->statusController.isDockumentsInside()) {
    this->statusController.setTrailerStatus(rec_status);
    this->relayController.handleTrailer(this->statusController.getTrailerStatus());
  }
}

void DeviceController::handleDocuments(const char* rec_status) {
    this->relayController.handleDocumentBox((char*)rec_status, this->statusController.isDockumentsInside());
}

bool DeviceController::compare(const char* src, const char* dst) {
    for(int i = 0; src[i] != '\0'; i++) {
        if (src[i] != dst[i]) {
            return false;
        }
    }
    return true;
}

void DeviceController::pingStatus() {
  if(ping_timer == 0) {
    this->publish(PUB_TOPIC_TRAILER.c_str(), this->statusController.getTrailerStatus());
    this->publish(PUB_TOPIC_DOCUMENTS.c_str(), this->statusController.getDocumentsStatus());
    this->publish(PUB_TOPIC_LIGHTS.c_str(), ACTIVE);
    Serial.print("trailer   | send: "); Serial.println(this->statusController.getTrailerStatus());
    Serial.print("documents | send: "); Serial.println(this->statusController.getDocumentsStatus());
    Serial.print("lights    | send: "); Serial.println(ACTIVE);
    ping_timer.start(ping_time);
  }
}
