#include "ExpandedNeoPixel.h"
#include "led_mode.h"
#include "rainbow_wheel.h"

void RainbowWheel::loop() {
    static uint8_t wheelPos = 0;
    static uint32_t prevMillis = 0;
    const uint16_t delayTime = 100; // Adjust this value to control the speed of the rainbow effect

    // Check if enough time has passed to update the rainbow effect
    if (millis() - prevMillis >= delayTime) {
        prevMillis = millis();
        
        // Iterate through each LED on the outside of the neopixel
        for (uint8_t i = 1; i < MAX_PIXELS; i++) {
            // Calculate the color for the current LED based on the wheel position
            uint32_t color = Wheel((i + wheelPos) % 256);
            
            // Set the color of the current LED
            neopixel.setPixelColor(i, color);
        }
        
        // Show the updated colors on the neopixel
        neopixel.show();
        
        // Increment the wheel position for the next iteration
        wheelPos++;
    }
}

// Helper function to calculate the color based on the wheel position
uint32_t RainbowWheel::Wheel(byte wheelPos) {
    wheelPos = 255 - wheelPos;
    if (wheelPos < 85) {
        return neopixel.Color(255 - wheelPos * 3, 0, wheelPos * 3);
    }
    if (wheelPos < 170) {
        wheelPos -= 85;
        return neopixel.Color(0, wheelPos * 3, 255 - wheelPos * 3);
    }
    wheelPos -= 170;
    return neopixel.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

void RainbowWheel::startup() {
    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        neopixel.setPixelColor(i, neopixel.Color(255, 0, 0));
        neopixel.show();
        delay(100);
    }
    delay(500);
    neopixel.clear();
    neopixel.show();
}

void RainbowWheel::shutdown() {
    neopixel.clear();
    neopixel.show();
}
