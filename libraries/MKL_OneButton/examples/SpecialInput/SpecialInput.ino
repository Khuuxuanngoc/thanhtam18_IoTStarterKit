/*
 * SpecialInput.ino - Example for the OneButtonLibrary library.
 * This is a sample sketch to show how to use the OneClick library on other input sources than standard digital pins.
 *
 * The library internals are explained at
 * http://www.mathertel.de/Arduino/OneButtonLibrary.aspx
 *
 * Setup a test circuit:
 * * Connect a pushbutton to pin 2 (ButtonPin) and ground.
 *
 * The sketch shows how to setup the library and bind the functions (singleClick, doubleClick) to the events.
 * In the loop function the button.tick function must be called as often as you like.
 *
 * * 22.01.2021 created by Matthias Hertel
 * * 07.02.2023 ESP32 Support added.
 */

#include "Arduino.h"
#include "MKL_OneButton.h"

// This is an example on how to use the OneClick library on other input sources than standard digital pins.
// 1. do not use a pin in the initialization of the OneClick library.
// 2. pass the input state to the tick function.

// You can also find how to create an instance in setup and not by declaration.
// You can also find how to use inline callback functions.

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO_EVERY)
#define PIN_INPUT 2

#elif defined(ESP8266)
#define PIN_INPUT D3

#elif defined(ESP32)
// Example pin assignments for a ESP32 board
// Some boards have a BOOT switch using GPIO 0.
#define PIN_INPUT 0

#endif


// OneButton instance will be created in setup.
MKL_OneButton *button;

void fClicked(void *s) {
  Serial.print("Click:");
  Serial.println((char *)s);
}

static void fDoubleClicked(void *oneButton) {
  MKL_OneButton *button = (MKL_OneButton *)oneButton;
  Serial.print("pin=");
  Serial.print(button->pin());
  Serial.print(" state=");
  Serial.println(button->state());
}

void setup() {
  Serial.begin(115200);
  Serial.println("One Button Example with custom input.");

  // create the OneButton instance without a pin.
  button = new MKL_OneButton();

  // Here is an example on how to use a parameter to the registered functions:
  button->attachClick(fClicked, (void *)"me");
  button->attachDoubleClick(fDoubleClicked, &button);

  // Here is an example on how to use an inline function:
  button->attachDoubleClick([]() {
    Serial.println("DoubleClick");
  });

  // setup your own source of input:
  pinMode(PIN_INPUT, INPUT_PULLUP);

}  // setup()

void loop() {
  // read your own source of input:
  bool isPressed = (digitalRead(PIN_INPUT) == LOW);

  // call tick frequently with current push-state of the input
  button->tick(isPressed);
}  // loop()
