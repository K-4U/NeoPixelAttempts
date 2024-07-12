#include <Adafruit_NeoPixel.h>
#include "ExpandedNeoPixel.h"

void ExpandedNeoPixel::setPixelColorWithDelay(uint16_t pixelIndex, Colour targetColor, uint32_t delayTime) {
    targetColors[pixelIndex].targetColor = targetColor;
    targetColors[pixelIndex].currentColor = getPixelColor(pixelIndex);
    targetColors[pixelIndex].timeRemaining = delayTime;
}

void ExpandedNeoPixel::setAllPixelsColorWithDelay(Colour targetColor, uint32_t delayTime) {
    for (uint16_t i = 0; i < numPixels(); i++) {
        setPixelColorWithDelay(i, targetColor, delayTime);
    }
}

void ExpandedNeoPixel::setPixelColor(uint16_t pixelIndex, Colour color) {
    targetColors[pixelIndex].targetColor = color;
    targetColors[pixelIndex].currentColor = color;
    targetColors[pixelIndex].timeRemaining = 0;
    Adafruit_NeoPixel::setPixelColor(pixelIndex, color.toNeoPixelColor());
}

void ExpandedNeoPixel::loop() {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1) {
        previousMillis = currentMillis;
    
        for (uint16_t i = 0; i < numPixels(); i++) {
            if (targetColors[i].timeRemaining > 0) {
                targetColors[i].timeRemaining--;

                if(targetColors[i].targetColor.red < targetColors[i].currentColor.red) {
                    uint8_t redDiff = targetColors[i].currentColor.red - targetColors[i].targetColor.red;
                    uint8_t redStep = redDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.red -= redStep;
                } else if (targetColors[i].targetColor.red > targetColors[i].currentColor.red) {
                    uint8_t redDiff = targetColors[i].targetColor.red - targetColors[i].currentColor.red;
                    uint8_t redStep = redDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.red += redStep;
                }

                if(targetColors[i].targetColor.green < targetColors[i].currentColor.green) {
                    uint8_t greenDiff = targetColors[i].currentColor.green - targetColors[i].targetColor.green;
                    uint8_t greenStep = greenDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.green -= greenStep;
                } else if (targetColors[i].targetColor.green > targetColors[i].currentColor.green) {
                    uint8_t greenDiff = targetColors[i].targetColor.green - targetColors[i].currentColor.green;
                    uint8_t greenStep = greenDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.green += greenStep;
                }

                if(targetColors[i].targetColor.blue < targetColors[i].currentColor.blue) {
                    uint8_t blueDiff = targetColors[i].currentColor.blue - targetColors[i].targetColor.blue;
                    uint8_t blueStep = blueDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.blue -= blueStep;
                } else if(targetColors[i].targetColor.blue > targetColors[i].currentColor.blue){
                    uint8_t blueDiff = targetColors[i].targetColor.blue - targetColors[i].currentColor.blue;
                    uint8_t blueStep = blueDiff / targetColors[i].timeRemaining;
                    targetColors[i].currentColor.blue += blueStep;
                }

                Adafruit_NeoPixel::setPixelColor(i, targetColors[i].currentColor.toNeoPixelColor());
            }
        }
        show();
    }
}

bool ExpandedNeoPixel::isPixelMoving(uint16_t pixelIndex) {
    return targetColors[pixelIndex].timeRemaining > 0;
}

uint32_t ExpandedNeoPixel::getTimeRemaining(uint16_t pixelIndex) {
    return targetColors[pixelIndex].timeRemaining;
}

