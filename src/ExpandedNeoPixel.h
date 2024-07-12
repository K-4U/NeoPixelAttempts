
#ifndef EXPANDEDNEOPIXEL_H
#define EXPANDEDNEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include "Ramp.h"

struct Colour;

struct Colour {
    rampUnsignedChar red;
    rampUnsignedChar green;
    rampUnsignedChar blue;

    uint32_t toNeoPixelColor() {
        return ((uint32_t)red.getValue() << 16) | ((uint32_t)green.getValue() << 8) | blue.getValue();
    }
};

class ExpandedNeoPixel : public Adafruit_NeoPixel {
    private:
        Colour* ledRamps;

    public:
        ExpandedNeoPixel(uint16_t numPixels, uint8_t pin, uint8_t type)
            : Adafruit_NeoPixel(numPixels, pin, type) {
                ledRamps = new Colour[numPixels];
        }

        void setPixelColorWithDelay(uint16_t pixelIndex, uint32_t targetColor, uint32_t delayTime);
        void setAllPixelsColorWithDelay(uint32_t targetColor, uint32_t delayTime);
        void setPixelColor(uint16_t pixelIndex, uint32_t color);
        void loop();
        bool isPixelMoving(uint16_t pixelIndex);
};

#endif // EXPANDEDNEOPIXEL_H
