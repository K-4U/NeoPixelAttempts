#include <Arduino.h>
#include "ExpandedNeoPixel.h"
#include <vector.h>
#include "led_mode.h"
#include "purple_breathing.h"
#include "rainbow_wheel.h"
#include "fire.h"

#define BUTTON_PIN 7
#define LED_DATA_PIN 5

#define DEBUG_LED_PIN 13

ExpandedNeoPixel jewel = ExpandedNeoPixel(MAX_PIXELS, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
LedMode* modes[] = {new PurpleBreathing(jewel), new RainbowWheel(jewel), new Fire(jewel)};

void setup()
{
  // Initialize serial communication
  Serial.begin(256000);
  // while (!Serial) {
    ; // Wait for serial port to connect
  // }
  Serial.println("Serial communication initialized");
  // modes.push_back(new PurpleBreathing(jewel));
  // modes.push_back(new RainbowWheel(jewel));

  // Set the button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // Set the LED pin as an output
  pinMode(DEBUG_LED_PIN, OUTPUT);

  digitalWrite(DEBUG_LED_PIN, 1);
  // Send a message over UART
  // Serial.println("Arduino has started");
  // Serial.println("Defining jewel");

  jewel.begin();
  jewel.show();
  for (uint8_t i = 0; i < MAX_PIXELS; i++)
  {
    // Serial << "Setting " << i << " to white" << '\n';
    jewel.setPixelColor(i, Colour(0, 255, 0));
    jewel.show();
    delay(100);
  }
  delay(500);
  jewel.clear();
  jewel.show();
  digitalWrite(DEBUG_LED_PIN, 0);
  // jewel.setAllPixelsColorWithDelay(jewel.Color(0, 255, 0), 1000);
}

static bool buttonPressed = false;
uint16_t ledOn = 0;
uint8_t modeIndex = 0;

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


