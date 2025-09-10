/*
 * F1_Lights.ino - Main Arduino File
 * F1 Race Light System
 * 
 * This is the main Arduino sketch file that coordinates all components
 */

#include "LightController.h"
#include "ButtonHandler.h"
#include "RaceManager.h"

// Global objects
LightController lights;
ButtonHandler button;
RaceManager race;

void setup() {
  Serial.begin(9600);
  
  // Initialize all components
  lights.init();
  button.init();
  race.init();
  
  Serial.println("F1 Race Light System Ready!");
  Serial.println("Press any key in Serial Monitor to start sequence");
  Serial.println("Press button for safety car");
}

void loop() {
  // Update button state
  button.update();
  
  // Handle race state machine
  race.update();
  
  // Check for safety car deployment
  if (button.isPressed() && race.canDeploySafetyCar()) {
    race.deploySafetyCar();
  }
  
  // Check for serial input to start sequence
  if (Serial.available() > 0 && race.isWaiting()) {
    Serial.read(); // Clear the input
    race.startSequence();
  }
}