/*
 * LightController.cpp
 * Handles all LED operations for the F1 race light system
 */

#include "LightController.h"
#include <Arduino.h>

LightController::LightController() : yellowBlinkState(false), lastYellowBlink(0) {
  // Constructor - initialize member variables
}

void LightController::init() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < NUM_RED_LIGHTS; i++) {
    pinMode(RED_LIGHTS[i], OUTPUT);
    digitalWrite(RED_LIGHTS[i], LOW);
  }
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  
  // Start with green light on (track clear)
  digitalWrite(GREEN_LIGHT, HIGH);
}

void LightController::turnOnRedLight(int index) {
  if (index >= 0 && index < NUM_RED_LIGHTS) {
    digitalWrite(RED_LIGHTS[index], HIGH);
    Serial.print("Red light ");
    Serial.print(index + 1);
    Serial.println(" ON");
  }
}

void LightController::turnOffAllRed() {
  for (int i = 0; i < NUM_RED_LIGHTS; i++) {
    digitalWrite(RED_LIGHTS[i], LOW);
  }
}

void LightController::turnOnAllRed() {
  for (int i = 0; i < NUM_RED_LIGHTS; i++) {
    digitalWrite(RED_LIGHTS[i], HIGH);
  }
}

void LightController::setGreenLight(bool state) {
  digitalWrite(GREEN_LIGHT, state ? HIGH : LOW);
}

void LightController::setYellowLight(bool state) {
  digitalWrite(YELLOW_LIGHT, state ? HIGH : LOW);
}

void LightController::updateBlinkingYellow() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastYellowBlink >= YELLOW_BLINK_INTERVAL) {
    yellowBlinkState = !yellowBlinkState;
    digitalWrite(YELLOW_LIGHT, yellowBlinkState ? HIGH : LOW);
    lastYellowBlink = currentTime;
  }
}

void LightController::allLightsOff() {
  turnOffAllRed();
  setGreenLight(false);
  setYellowLight(false);
}

void LightController::showStartLights() {
  allLightsOff();
  setGreenLight(true);
}

void LightController::showRaceLights() {
  turnOffAllRed();
  setYellowLight(false);
  setGreenLight(true);
}

void LightController::showSafetyCarLights() {
  setGreenLight(false);
  // Yellow light blinking is handled by updateBlinkingYellow()
}

void LightController::showStoppedLights() {
  setGreenLight(false);
  setYellowLight(false);
  turnOnAllRed();
}