#pragma once
#include "Consts.h"
#include <Adafruit_NeoPixel.h>
#include "Timer.h"

class LightsController {
private:
    Timer move_timer = Timer(0);

    Adafruit_NeoPixel top_strip = Adafruit_NeoPixel(TOP_NUM_LEDS, UP_DOCUMENTS_BOX, NEO_RGB + NEO_KHZ800);
    uint8_t top_r = 0, top_g = 0, top_b = 0;
    int top_position = 0;
    bool top_way = true;

    Adafruit_NeoPixel bot_strip = Adafruit_NeoPixel(BOT_NUM_LEDS, DOWN_DOCUMENTS_BOX, NEO_RGB + NEO_KHZ800);
    uint8_t bot_r = 0, bot_g = 0, bot_b = 0;
    int bot_position = 0;
    bool bot_way = true;

    void setStripColor();
    void updatePosition();

public:
    void setup();
    void update();
    void off();
    void upLightOn();
    void upLightOff();
    void downLightOn();
    void downLightOff();
};

void LightsController::update() {
    updatePosition();
}

void LightsController::setup() {
    this->bot_strip.begin();
    this->top_strip.begin();
    this->move_timer.start();
}

void LightsController::off() {
    this->upLightOff();
    this->downLightOff();
}

void LightsController::upLightOn() {
    top_r = TOP_R; top_g = TOP_G; top_b = TOP_B;
}

void LightsController::upLightOff() {
    top_r = 0; top_g = 0; top_b = 0;
}

void LightsController::downLightOn() {
    bot_r = BOT_R; bot_g = BOT_G; bot_b = BOT_B;
}

void LightsController::downLightOff() {
    bot_r = 0; bot_g = 0; bot_b = 0;
}

void LightsController::setStripColor() {
  for (int i = 0; i < TOP_NUM_LEDS; i++) {
    if (i == top_position) {
        this->top_strip.setPixelColor(i, top_strip.Color(0, 0, 0));
    } else {
        this->top_strip.setPixelColor(i, top_strip.Color(top_g, top_r, top_b));
    }
  }
  for (int i = 0; i < BOT_NUM_LEDS; i++) {
    if (i == bot_position) {
        this->bot_strip.setPixelColor(i, bot_strip.Color(0, 0, 0));
    } else {
        this->bot_strip.setPixelColor(i, bot_strip.Color(bot_g, bot_r, bot_b));
    }
  }
  this->bot_strip.show();
  this->top_strip.show();
}

void LightsController::updatePosition() {
    if (this->move_timer == 0) {

        top_position += top_way ? -1 : 1;
        bot_position += bot_way ? -1 : 1;

        if (top_position == TOP_NUM_LEDS) {
            top_way = !top_way; top_position = TOP_NUM_LEDS-1;
        } else if(top_position < 0) {
            top_way = !top_way; top_position = 0;
        }
        if (bot_position == BOT_NUM_LEDS) {
            bot_way = !bot_way; bot_position = BOT_NUM_LEDS-1;
        } else if(bot_position < 0) {
            bot_way = !bot_way; bot_position = 0;
        }
        
        setStripColor();
        this->move_timer.start(100);
    }
}
