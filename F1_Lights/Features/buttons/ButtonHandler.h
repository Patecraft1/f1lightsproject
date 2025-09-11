/*
 * ButtonHandler.h
 * Header file for button input handling
 */

#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

// Pin definitions
const int BUTTON_PIN = 9; // Button for safety car

// Timing constants
const unsigned long DEBOUNCE_DELAY = 50; // 50ms debounce delay

class ButtonHandler {
private:
  bool buttonPressed;
  bool lastButtonState;
  unsigned long lastDebounceTime;

public:
  ButtonHandler();
  
  // Initialization
  void init();
  
  // Update button state (call this in loop)
  void update();
  
  // Check if button was pressed (returns true once per press)
  bool isPressed();
  
  // Check current button state (for continuous checking)
  bool isCurrentlyPressed();
};

// Global instance declaration
extern ButtonHandler button;

#endif