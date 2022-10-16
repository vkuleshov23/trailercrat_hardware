#pragma once

#include <string>

#define mqtt_user                   "trailercraft_app"
#define mqtt_pass                   "GfhfgkfY123"
#define mqtt_server                 "188.246.224.20"
#define mqtt_port                   4646

#define ssid                        "aaaa1234"
#define password                    "12345678"

std::string serail_number = "1";

std::string mqtt_client = "ESP/" + serail_number + "/CLIENT";

std::string SUB_TOPIC_TRAILER = "kogortam/in/" + serail_number + "/trailer";
std::string PUB_TOPIC_TRAILER = "kogortam/out/" + serail_number + "/trailer";

std::string SUB_TOPIC_DOCUMENTS = "kogortam/in/" + serail_number + "/documents";
std::string PUB_TOPIC_DOCUMENTS = "kogortam/out/" + serail_number + "/documents";


std::string SUB_TOPIC_LIGHTS = "kogortam/in/" + serail_number + "/lights";
std::string PUB_TOPIC_LIGHTS = "kogortam/out/" + serail_number + "/lights";
