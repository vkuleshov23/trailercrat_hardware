#include <Arduino.h>
#include "Consts.h"
#include "Timer.h"
#include "LightsController.h"

#define LOW 0x1
#define HIGH 0x0

class RelayController {
private:
    bool need_close = true;
    bool upLight = false;
    bool isLight = false;
    Timer close_timer = Timer(0);
    Timer blink_timer = Timer(0);
    Timer one_blink_timer = Timer(0);
    LightsController lightsController;
public:
    void setup();
    void update(bool documents_inside);
    bool compare(const char* src, char* dst);
    void handleTrailer(char* trailer_status);
    void handleDocumentBox(char* documents_status, bool documents_inside);
    void handleLights(char* documents_status, bool documents_inside);
    void openTrailer();
    void closeTrailer();
    void openDocumentsBox();
    void closeDocumentsBox();
    void lightUpTurnSignals();
    void turnOffTurnSignals();
    void lightUpHeadlights();
    void turnOffHeadlights();
};

void RelayController::update(bool documents_inside) {
    if (need_close) {
        if (close_timer == 0) {
            this->closeDocumentsBox();
            need_close = false;
        }
        if (!documents_inside) {
            if(upLight == true) {
                this->lightsController.upLightOn();
            } else {
                this->lightsController.downLightOn();
            }
        } else {
            this->lightsController.off();
        }
    } else {
        this->lightsController.off();
    }
    if(blink_timer != 0) {
        this->lightUpHeadlights();        
        if(one_blink_timer == 0) {
            if (isLight) this->lightUpTurnSignals();
            else this->turnOffTurnSignals();
            isLight = !isLight;
            one_blink_timer.start(TURN_SIGNAL_ONE_BLINK_TIME);
        }
    } else {
        this->turnOffHeadlights();
        this->turnOffTurnSignals();
    }
    this->lightsController.update();
}

void RelayController::setup() {
    pinMode(TRAILER_RELAY_PIN, OUTPUT);
    pinMode(DOCUMENTS_RELAY_PIN, OUTPUT);
    pinMode(TURN_SIGNALS_RELAY_PIN, OUTPUT);
    pinMode(HEADLIGHTS_RELAY_PIN, OUTPUT);
    closeDocumentsBox();
    closeTrailer();
    this->lightsController.setup();
}

void RelayController::handleTrailer(char* trailer_status) {
    if(compare(OPEN, trailer_status)) {
      this->openTrailer();
    }else if (compare(CLOSE, trailer_status)) {
        this->closeTrailer();
    }
}

void RelayController::handleDocumentBox(char* documents_status, bool documents_inside) {
    if(compare(OPEN, documents_status)) {
        if (documents_inside) {
            this->openDocumentsBox();
            upLight = false;
            need_close = true;
            close_timer.start(CLOSE_DOCUMENT_BOX_TIME);
        }
    } else {
        this->closeDocumentsBox();
        upLight = true;
        need_close = true;
        close_timer.start(CLOSE_DOCUMENT_BOX_TIME);
    }
}

void RelayController::handleLights(char* lights_status, bool documents_inside) {
    if (documents_inside) {
        if(compare(ON, lights_status) || compare(OPEN, lights_status)) {
            blink_timer.start(BLINK_TIME);
        } else {
            blink_timer.start(0);
        }
    } else {
        blink_timer.start(0);
    }
}

void RelayController::openTrailer() {
    digitalWrite(TRAILER_RELAY_PIN, HIGH);
    // delay(100);
    // digitalWrite(TRAILER_RELAY_PIN, LOW);
}
void RelayController::closeTrailer() {
    // digitalWrite(TRAILER_RELAY_PIN, HIGH);
    // delay(100);
    digitalWrite(TRAILER_RELAY_PIN, LOW);
}
void RelayController::openDocumentsBox() {
    digitalWrite(DOCUMENTS_RELAY_PIN, HIGH);
}
void RelayController::closeDocumentsBox() {
    digitalWrite(DOCUMENTS_RELAY_PIN, LOW);
}
void RelayController::lightUpTurnSignals() {
    digitalWrite(TURN_SIGNALS_RELAY_PIN, HIGH);
}
void RelayController::turnOffTurnSignals() {
    digitalWrite(TURN_SIGNALS_RELAY_PIN, LOW);
}
void RelayController::lightUpHeadlights() {
    digitalWrite(HEADLIGHTS_RELAY_PIN, HIGH);
}
void RelayController::turnOffHeadlights() {
    digitalWrite(HEADLIGHTS_RELAY_PIN, LOW);
}
bool RelayController::compare(const char* src, char* dst) {
    for(int i = 0; src[i] != '\0'; i++) {
        if (src[i] != dst[i]) {
            return false;
        }
    }
    return true;
}
