#ifndef LED_MODE_H
#define LED_MODE_H

#define MAX_PIXELS 7

/**
 * @brief The base class for LED modes.
 *
 * This class provides an interface for implementing different LED modes.
 * Subclasses of this class should implement the `loop()` function to define the
 * behavior of the LED mode.
 */
class LedMode {
   public:
    /**
     * @brief The main loop function for the LED mode.
     *
     * This function should be implemented by subclasses to define the behavior
     * of the LED mode.
     */
    virtual void loop() = 0;
    virtual void startup() = 0;
    virtual void shutdown() = 0;
};

#endif  // LED_MODE_H