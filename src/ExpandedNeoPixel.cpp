#include <Adafruit_NeoPixel.h>
#include "ExpandedNeoPixel.h"

void ExpandedNeoPixel::setPixelColorWithDelay(uint16_t pixelIndex, uint32_t targetColor, uint32_t delayTime) {
    ledRamps[pixelIndex].red.go((targetColor >> 16) & 0xFF, delayTime);
    ledRamps[pixelIndex].green.go((targetColor >> 8) & 0xFF, delayTime);
    ledRamps[pixelIndex].blue.go(targetColor & 0xFF, delayTime);
}

void ExpandedNeoPixel::setAllPixelsColorWithDelay(uint32_t targetColor, uint32_t delayTime) {
    for (uint16_t i = 0; i < numPixels(); i++) {
        setPixelColorWithDelay(i, targetColor, delayTime);
    }
}

void ExpandedNeoPixel::setPixelColor(uint16_t pixelIndex, uint32_t targetColor) {
    setPixelColorWithDelay(pixelIndex, targetColor, 0);
    Adafruit_NeoPixel::setPixelColor(pixelIndex, targetColor);
}

void ExpandedNeoPixel::loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1) {
        previousMillis = currentMillis;
    
        for (uint16_t i = 0; i < numPixels(); i++) {
            uint8_t red = ledRamps[i].red.getValue();
            uint8_t green = ledRamps[i].green.getValue();
            uint8_t blue = ledRamps[i].blue.getValue();

            if(ledRamps[i].red.isRunning()) {
                ledRamps[i].red.update();
            }
            if(ledRamps[i].green.isRunning()) {
                ledRamps[i].green.update();
            }
            if(ledRamps[i].blue.isRunning()) {
                ledRamps[i].blue.update();
            }

            Adafruit_NeoPixel::setPixelColor(i, Color(red, green, blue));
        }
        show();
    }
}

bool ExpandedNeoPixel::isPixelMoving(uint16_t pixelIndex) {
    return ledRamps[pixelIndex].red.isRunning() || ledRamps[pixelIndex].green.isRunning() || ledRamps[pixelIndex].blue.isRunning();
}


