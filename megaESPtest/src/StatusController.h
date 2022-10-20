#pragma once
#include "RFID.h"
#include "Consts.h"
#include "Timer.h"
#include <Arduino.h>

class StatusController {
private:
    RFID rfid = RFID();
    Timer rfid_read_timer = Timer(100);
    byte read_try = 0;  
    char trailer_status[20];
    char documets_status[20];
    bool documents_inside = false;
    bool last_documents_state = false;
    void set_status(const char* stat, char status[]);
public:
    char* getTrailerStatus() {return this->trailer_status;}
    char* getDocumentsStatus() {return this->documets_status;}
    void setup();
    bool documentStatusWasUpdated();
    void readData();
    bool isDockumentsInside();
    void setTrailerStatus(const char* rec_status);
    void setDocumentsStatus(const char* rec_status);
};

void StatusController::setup() {
    rfid.setup();
    rfid_read_timer.start();
    setTrailerStatus(OPEN);
    setDocumentsStatus(NO_CARD);
}

bool StatusController::documentStatusWasUpdated() {
    if(last_documents_state != documents_inside) {
        last_documents_state = documents_inside;
        return true;
    }
    return false;
}

void StatusController::readData() {
    if (!rfid.try_read_uid()) {
        if (read_try == 10) {
            setDocumentsStatus(NO_CARD);
            read_try = 0;
            documents_inside = false;
        }
        read_try += 1;
    } else {
        // const char* new_status = rfid.readCard();
        if (rfid.isEqualsEthalon()) {
            documents_inside = true;
            setDocumentsStatus(HAVE_CARD);
        }
        // set_status(new_status, documets_status);
        read_try = 0;
    }
    rfid_read_timer.start(5000);
}

void StatusController::set_status(const char* stat, char status[]) {
  int i = 0;
  while(stat[i] !=  '\0') {
    status[i] = stat[i];
    i++;
  }
  status[i] = '\0';
}


void StatusController::setTrailerStatus(const char* rec_status) {
    set_status(rec_status, trailer_status);
}

void StatusController::setDocumentsStatus(const char* rec_status) {
    set_status(rec_status, documets_status);
}

bool StatusController::isDockumentsInside() {
    return documents_inside;
}
