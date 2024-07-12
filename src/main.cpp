#include <Arduino.h>
#include "ExpandedNeoPixel.h"
#include <vector.h>
#include "led_mode.h"
#include "breathing.h"
#include "rainbow_wheel.h"
#include "fire.h"

#define BUTTON_PIN 7
#define LED_DATA_PIN 5

#define DEBUG_LED_PIN 13

ExpandedNeoPixel jewel = ExpandedNeoPixel(MAX_PIXELS, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
LedMode* modes[] = {new Breathing(jewel, jewel.Color(80, 0, 80), jewel.Color(255, 0, 255), 1000),
 new RainbowWheel(jewel),
  new Fire(jewel),
   new Breathing(jewel, jewel.Color(128, 128, 0), jewel.Color(0, 255, 255), 1000),
   new Breathing(jewel, jewel.Color(0, 128, 0), jewel.Color(0, 255, 0), 10000)
   };
static bool buttonPressed = false;
uint16_t ledOn = 0;
uint8_t modeIndex = 0;


void setup()
{
   // Set the button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // Set the LED pin as an output
  pinMode(DEBUG_LED_PIN, OUTPUT);

  digitalWrite(DEBUG_LED_PIN, 1);

  jewel.begin();
  jewel.show();
  //Do a startup animation
  for (uint8_t i = 0; i < MAX_PIXELS; i++)
  {
    jewel.setPixelColor(i, jewel.Color(0, 255, 0));
    jewel.show();
    delay(100);
  }
  delay(500);
  jewel.clear();
  jewel.show();
  digitalWrite(DEBUG_LED_PIN, 0);

  //Do the startup of the first mode
  modes[modeIndex]->startup();
}

bool isButtonPressed() {
  // Read the state of the button
  int buttonState = digitalRead(BUTTON_PIN);

  // Check if the button is pressed
  if (buttonState == HIGH && !buttonPressed){
    buttonPressed = true;
  } else if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
    return true;
  }
  return false;
}

uint32_t ledOnMillis = 0;
uint32_t previousMillis = 0;
void loop()
{
  // Run the code only when the button has been pressed and depressed
  if (isButtonPressed()) {
    ledOnMillis = millis();
    digitalWrite(DEBUG_LED_PIN, 1);

    // Increment the mode index
    modes[modeIndex]->shutdown();
    modeIndex++;
    if (modeIndex >= sizeof(modes) / sizeof(modes[0])) {
      modeIndex = 0;
    }
    modes[modeIndex]->startup();
  }

  if(millis() - ledOnMillis > 1000) {
    digitalWrite(DEBUG_LED_PIN, 0);
  }

  // Run the loop function of the current mode
  modes[modeIndex]->loop();
  jewel.loop();

}


