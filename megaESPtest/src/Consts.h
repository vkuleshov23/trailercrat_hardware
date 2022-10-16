#pragma once
#include <Arduino.h>

#define led_pin1 24
#define led_pin2 28
#define led_pin3 30

#define RST_PIN                     49
#define SS_PIN                      53

#define TRAILER_RELAY_PIN           34
#define DOCUMENTS_RELAY_PIN         35
#define TURN_SIGNALS_RELAY_PIN      36
#define HEADLIGHTS_RELAY_PIN        37
#define UP_DOCUMENTS_BOX            38
#define DOWN_DOCUMENTS_BOX          39

#define ON                          "ON"
#define OFF                         "OFF"
#define OPEN                        "OPEN"
#define CLOSE                       "CLOSE"
#define ACTIVE                      "ACTIVE"
#define NO_CARD                     "ABSENT"
#define HAVE_CARD                   "PRESENT"

#define TOP_NUM_LEDS 5
#define TOP_R 0
#define TOP_G 183
#define TOP_B 255

#define BOT_NUM_LEDS 5
#define BOT_R 0
#define BOT_G 183
#define BOT_B 255


#define BLINK_TIME                  10000
#define TURN_SIGNAL_ONE_BLINK_TIME  1000
#define ping_time                   10000
#define CLOSE_DOCUMENT_BOX_TIME     10000


byte ethalon_card[] = {83, 52, 172, 172};

String serail_number = "1";

String SUB_TOPIC_TRAILER = "kogortam/in/" + serail_number + "/trailer";
String PUB_TOPIC_TRAILER = "kogortam/out/" + serail_number + "/trailer";

String SUB_TOPIC_DOCUMENTS = "kogortam/in/" + serail_number + "/documents";
String PUB_TOPIC_DOCUMENTS = "kogortam/out/" + serail_number + "/documents";


String SUB_TOPIC_LIGHTS = "kogortam/in/" + serail_number + "/lights";
String PUB_TOPIC_LIGHTS = "kogortam/out/" + serail_number + "/lights";