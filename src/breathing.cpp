#include "breathing.h"

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

static uint32_t prevMillis = 0;
static bool toTarget = true;
void Breathing::loop() {
    if (millis() - prevMillis >= delayMs) {
        prevMillis = millis();
        if (toTarget) {
            neopixel.setAllPixelsColorWithDelay(targetColor, delayMs);
            toTarget = false;
        } else {
            neopixel.setAllPixelsColorWithDelay(sourceColor, delayMs);
            toTarget = true;
        }
    }
}

void Breathing::startup() {
    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        neopixel.setPixelColor(i, targetColor);
        neopixel.show();
        delay(100);
    }
    delay(500);
    neopixel.clear();
    neopixel.show();
    neopixel.setAllPixelsColorWithDelay(sourceColor, delayMs);
    prevMillis = millis();
}

void Breathing::shutdown() {
    neopixel.clear();
    neopixel.show();
}