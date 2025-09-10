/*
 * ButtonHandler.cpp
 * Handles button input with debouncing for safety car deployment
 */

#include "ButtonHandler.h"
#include <Arduino.h>

ButtonHandler::ButtonHandler() : 
  buttonPressed(false), 
  lastButtonState(false),
  lastDebounceTime(0) {
  // Constructor - initialize member variables
}

void ButtonHandler::init() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void ButtonHandler::update() {
  bool currentButtonState = !digitalRead(BUTTON_PIN); // Inverted due to pullup
  unsigned long currentTime = millis();
  
  // Debounce the button
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = currentTime;
  }
  
  // If enough time has passed since the last state change
  if ((currentTime - lastDebounceTime) > DEBOUNCE_DELAY) {
    // If button state has actually changed and is now pressed
    if (currentButtonState && !buttonPressed) {
      buttonPressed = true;
    }
  }
  
  lastButtonState = currentButtonState;
}

bool ButtonHandler::isPressed() {
  if (buttonPressed) {
    buttonPressed = false; // Reset the flag
    return true;
  }
  return false;
}

bool ButtonHandler::isCurrentlyPressed() {
  return !digitalRead(BUTTON_PIN); // Inverted due to pullup
}