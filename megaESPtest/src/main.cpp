#include <Arduino.h>
#include "DeviceController.h"

DeviceController deviceController;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  deviceController.setup();
}

void loop() {
   deviceController.update();
 
}