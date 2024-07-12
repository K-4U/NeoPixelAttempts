#ifndef PURPLE_BREATHING_H
#define PURPLE_BREATHING_H

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

class PurpleBreathing : public LedMode {
private:
    ExpandedNeoPixel& neopixel;
    uint8_t red, green, blue;
public:
    PurpleBreathing(ExpandedNeoPixel& neopixel) : neopixel(neopixel) {
        red = 0;
        green = 0;
        blue = 0;
    }

    void loop() override;
    void startup() override;
    void shutdown() override;

};

#endif // PURPLE_BREATHING_H