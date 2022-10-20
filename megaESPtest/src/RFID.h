#pragma once
#include <MFRC522.h>
#include "Consts.h"
#include <SPI.h>

class RFID {
private:
    MFRC522 mfrc522 = MFRC522(SS_PIN, RST_PIN);
public:
    void setup();
    bool try_read_uid();
    const char* readCard();
    void view_data ();
    bool isEqualsEthalon();
};

void RFID::setup() {
    SPI.begin();
    mfrc522.PCD_Init();
    mfrc522.PCD_DumpVersionToSerial();
    do {
        byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
        switch(v) {
            case 0x88: Serial.println(F(" = (clone)"));  return;
            case 0x90: Serial.println(F(" = v0.0"));     return;
            case 0x91: Serial.println(F(" = v1.0"));     return;
            case 0x92: Serial.println(F(" = v2.0"));     return;
            case 0x12: Serial.println(F(" = counterfeit chip"));     return;
            default:   Serial.println(F(" = (unknown)")); 
        }
        mfrc522.PCD_Reset();
        delay(1000);
    } while (true);
}

const char* RFID::readCard() {
    String uid;
    for (byte j = 0; j < mfrc522.uid.size; j++) {
        uid += ((char)mfrc522.uid.uidByte[j]);
        // Serial.print(uid[j]);
    }
    // Serial.println();
    return uid.c_str();
}


bool RFID::try_read_uid() {
    if (!mfrc522.PICC_IsNewCardPresent()) { 
        return false;
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return false;
    }
    // view_data();
    return true;
}



bool RFID::isEqualsEthalon() {
    if (sizeof(ethalon_card) == mfrc522.uid.size) {
        for(int i = 0; i < mfrc522.uid.size; i++) {
            if (ethalon_card[i] != mfrc522.uid.uidByte[i]) {
                return false;
            }
        }
        return true;
    }
    return false;

}

void RFID::view_data () {
    
  Serial.println("UID:");
  Serial.println();
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    Serial.print(mfrc522.uid.uidByte[j]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("type = ");
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
}