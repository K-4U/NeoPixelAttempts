#ifndef RAINBOW_WHEEL_H
#define RAINBOW_WHEEL_H

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

class RainbowWheel : public LedMode {
   private:
    ExpandedNeoPixel& neopixel;
    uint8_t red, green, blue;

    uint32_t Wheel(byte wheelPos);

   public:
    RainbowWheel(ExpandedNeoPixel& neopixel) : neopixel(neopixel) {
        red = 0;
        green = 0;
        blue = 0;
    }

    void loop() override;
    void startup() override;
    void shutdown() override;
};

#endif  // RAINBOW_WHEEL_H