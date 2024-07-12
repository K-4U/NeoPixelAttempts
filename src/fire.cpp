#include "fire.h"

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

const uint32_t fire_colors[] = {0x00EA5104, 0x00470B04, 0x00A40E04, 0x00FB7604,
                                0x00740A04, 0x00FCA204, 0x00BA0B04, 0x00CB2004,
                                0x00C93204, 0x00D83004, 0x00B82404, 0x008F0F04};

void Fire::loop() {
    static uint32_t prevMillis = 0;
    const uint16_t delayTime =
        100;  // Adjust this value to control the speed of the fire effect

    // Check if enough time has passed to update the fire effect
    if (millis() - prevMillis >= delayTime) {
        prevMillis = millis();
        for (uint8_t i = 0; i < MAX_PIXELS; i++) {
            uint8_t flicker = random(0, 10);
            neopixel.setPixelColorWithDelay(i, fire_colors[flicker], delayTime);
        }
    }
}

void Fire::startup() {
    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        neopixel.setPixelColor(i, neopixel.Color(255, 165, 0));
        neopixel.show();
        delay(100);
    }
    delay(500);
    neopixel.clear();
    neopixel.show();
}

void Fire::shutdown() {
    neopixel.clear();
    neopixel.show();
}