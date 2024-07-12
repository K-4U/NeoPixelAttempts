#ifndef PURPLE_BREATHING_H
#define PURPLE_BREATHING_H

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

class Breathing : public LedMode {
private:
    ExpandedNeoPixel& neopixel;
    uint32_t sourceColor;
    uint32_t targetColor;
    uint16_t delayMs;
public:
    Breathing(ExpandedNeoPixel& neopixel, uint32_t sourceColor, uint32_t targetColor, uint16_t delayMs) : neopixel(neopixel), delayMs(delayMs), sourceColor(sourceColor), targetColor(targetColor) {}

    void loop() override;
    void startup() override;
    void shutdown() override;

};

#endif // PURPLE_BREATHING_H