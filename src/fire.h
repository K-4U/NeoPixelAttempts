#ifndef FIRE_H
#define FIRE_H

#include "ExpandedNeoPixel.h"
#include "led_mode.h"

class Fire : public LedMode {
private:
    ExpandedNeoPixel& neopixel;
    uint8_t red, green, blue;
public:
    Fire(ExpandedNeoPixel& neopixel) : neopixel(neopixel) {
        red = 0;
        green = 0;
        blue = 0;
    }

    void loop() override;
    void startup() override;
    void shutdown() override;

};

#endif // FIRE_H