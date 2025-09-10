/*
 * RaceManager.cpp
 * Manages race states and timing for the F1 light system
 */

#include "RaceManager.h"
#include "LightController.h"
#include <Arduino.h>

// External reference to the lights object
extern LightController lights;

RaceManager::RaceManager() : 
  currentState(WAITING),
  currentRedLight(0),
  lastRedLightTime(0),
  raceStartTime(0),
  safetyCarStartTime(0) {
  // Constructor - initialize member variables
}

void RaceManager::init() {
  currentState = WAITING;
  currentRedLight = 0;
  
  // Initialize random seed
  randomSeed(analogRead(A0));
  
  // Set initial light state
  lights.showStartLights();
}

void RaceManager::update() {
  switch (currentState) {
    case WAITING:
      handleWaiting();
      break;
      
    case START_SEQUENCE:
      handleStartSequence();
      break;
      
    case RACING:
      handleRacing();
      break;
      
    case SAFETY_CAR:
      handleSafetyCar();
      break;
      
    case RACE_STOPPED:
      handleRaceStopped();
      break;
  }
}

void RaceManager::handleWaiting() {
  // Waiting for external trigger to start sequence
  // (handled in main loop)
}

void RaceManager::handleStartSequence() {
  unsigned long currentTime = millis();
  
  // Turn on red lights sequentially with random intervals
  if (currentRedLight < NUM_RED_LIGHTS) {
    if (currentTime - lastRedLightTime >= random(RED_LIGHT_MIN_DELAY, RED_LIGHT_MAX_DELAY)) {
      lights.turnOnRedLight(currentRedLight);
      currentRedLight++;
      lastRedLightTime = currentTime;
      
      if (currentRedLight == NUM_RED_LIGHTS) {
        Serial.println("All red lights on - waiting for start...");
        // Wait a random time before turning all lights off
        raceStartTime = currentTime + random(START_MIN_DELAY, START_MAX_DELAY);
      }
    }
  } else {
    // All red lights are on, wait for random time then start race
    if (currentTime >= raceStartTime) {
      startRace();
    }
  }
}

void RaceManager::handleRacing() {
  // Race is in progress - maintain green light
  // Safety car deployment handled externally
}

void RaceManager::handleSafetyCar() {
  // Update blinking yellow light
  lights.updateBlinkingYellow();
  
  // Auto-resume race after specified time
  if (millis() - safetyCarStartTime >= SAFETY_CAR_DURATION) {
    resumeRace();
  }
}

void RaceManager::handleRaceStopped() {
  // Race is stopped - maintain red lights
  // Could implement restart logic here
}

void RaceManager::startSequence() {
  Serial.println("\n=== STARTING F1 RACE SEQUENCE ===");
  
  lights.allLightsOff();
  
  currentState = START_SEQUENCE;
  currentRedLight = 0;
  lastRedLightTime = millis();
}

void RaceManager::startRace() {
  Serial.println("\n LIGHTS OUT AND AWAY WE GO! ");
  
  lights.showRaceLights();
  currentState = RACING;
}

void RaceManager::deploySafetyCar() {
  Serial.println("\n SAFETY CAR DEPLOYED ");
  
  lights.showSafetyCarLights();
  safetyCarStartTime = millis();
  currentState = SAFETY_CAR;
}

void RaceManager::resumeRace() {
  Serial.println("\n SAFETY CAR RETURNING - RACE RESUMED");
  
  lights.showRaceLights();
  currentState = RACING;
}

void RaceManager::stopRace() {
  Serial.println("\n RACE STOPPED ");
  
  lights.showStoppedLights();
  currentState = RACE_STOPPED;
}

void RaceManager::resetSystem() {
  Serial.println("\n SYSTEM RESET");
  
  lights.showStartLights();
  currentState = WAITING;
  currentRedLight = 0;
}

bool RaceManager::isWaiting() const {
  return currentState == WAITING;
}

bool RaceManager::canDeploySafetyCar() const {
  return (currentState == RACING || currentState == WAITING);
}

RaceState RaceManager::getCurrentState() const {
  return currentState;
}