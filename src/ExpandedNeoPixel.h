
#ifndef EXPANDEDNEOPIXEL_H
#define EXPANDEDNEOPIXEL_H

#include <Adafruit_NeoPixel.h>

struct Colour;

struct Colour {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Colour(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
    Colour(uint32_t color): red((color >> 16) & 0xFF), green((color >> 8) & 0xFF), blue(color & 0xFF) {}

    uint32_t toNeoPixelColor() {
        return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
    }
};

struct ColorData {
    Colour targetColor;
    Colour currentColor;
    uint32_t timeRemaining;
    ColorData() : targetColor(0, 0, 0), currentColor(0, 0, 0), timeRemaining(0) {}
};


class ExpandedNeoPixel : public Adafruit_NeoPixel {
    private:
        ColorData* targetColors;

    public:
        ExpandedNeoPixel(uint16_t numPixels, uint8_t pin, uint8_t type)
            : Adafruit_NeoPixel(numPixels, pin, type) {
                targetColors = new ColorData[numPixels];
        }

        void setPixelColorWithDelay(uint16_t pixelIndex, Colour targetColor, uint32_t delayTime);

        void setAllPixelsColorWithDelay(Colour targetColor, uint32_t delayTime);

        void setPixelColor(uint16_t pixelIndex, Colour color);
        void loop();
        bool isPixelMoving(uint16_t pixelIndex);
        uint32_t getTimeRemaining(uint16_t pixelIndex);
};

#endif // EXPANDEDNEOPIXEL_H
