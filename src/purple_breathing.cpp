#include "ExpandedNeoPixel.h"
#include "led_mode.h"
#include "purple_breathing.h"

static uint32_t prevMillis = 0;
void PurpleBreathing::loop() {
    static uint8_t brightness = 128;

    if(millis() - prevMillis >= 1000){
        prevMillis = millis();
        if(brightness == 128){
            brightness = 0;
        } else {
            brightness = 128;
        }
        neopixel.setAllPixelsColorWithDelay(Colour(brightness, 0, brightness), 1000);
    }
}


void PurpleBreathing::startup() {
    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        neopixel.setPixelColor(i, Colour(255, 0, 255));
        neopixel.show();
        delay(100);
    }
    delay(500);
    neopixel.clear();
    neopixel.show();
    neopixel.setAllPixelsColorWithDelay(Colour(128, 0, 128), 1000);
    prevMillis = millis();
}

void PurpleBreathing::shutdown() {
    neopixel.clear();
    neopixel.show();
}