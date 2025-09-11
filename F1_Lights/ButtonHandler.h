/*
 * ButtonHandler.h
 * Header file for button input handling
 */

#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

// Pin definitions
const int BUTTON_PIN = 9; // Button for safety car

// Timing constants
const unsigned long DEBOUNCE_DELAY = 50;

class ButtonHandler {
private:
  bool buttonPressed;
  bool lastButtonState;
  unsigned long lastDebounceTime;

public:
  ButtonHandler();
  
  void init();
  
  // Update button state
  void update();
  

  bool isPressed();
  

  bool isCurrentlyPressed();
};

// Global instance declaration
extern ButtonHandler button;

#endif