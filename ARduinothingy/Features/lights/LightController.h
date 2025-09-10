/*
 * LightController.h
 * Header file for LED control functionality
 */

#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

// Pin definitions
const int RED_LIGHTS[] = {2, 3, 4, 5, 6};  // 5 red LEDs for start sequence
const int GREEN_LIGHT = 7;                  // Green LED for race start
const int YELLOW_LIGHT = 8;                 // Yellow LED for safety car
const int NUM_RED_LIGHTS = 5;

// Timing constants
const unsigned long YELLOW_BLINK_INTERVAL = 500; // 500ms blink interval

class LightController {
private:
  bool yellowBlinkState;
  unsigned long lastYellowBlink;

public:
  LightController();
  
  // Initialization
  void init();
  
  // Red light controls
  void turnOnRedLight(int index);
  void turnOffAllRed();
  void turnOnAllRed();
  
  // Individual light controls
  void setGreenLight(bool state);
  void setYellowLight(bool state);
  
  // Special effects
  void updateBlinkingYellow();
  
  // State-based light patterns
  void allLightsOff();
  void showStartLights();
  void showRaceLights();
  void showSafetyCarLights();
  void showStoppedLights();
};

// Global instance declaration
extern LightController lights;

#endif