/*
 * RaceManager.h
 * Header file for race state management
 */

#ifndef RACEMANAGER_H
#define RACEMANAGER_H

// Race state enumeration
enum RaceState {
  WAITING,  
  START_SEQUENCE,
  RACING,
  SAFETY_CAR,
  RACE_STOPPED
};

// Timing constants (in milliseconds)
const unsigned long RED_LIGHT_MIN_DELAY = 1000;  // 1 second minimum
const unsigned long RED_LIGHT_MAX_DELAY = 3000;  // 3 seconds maximum
const unsigned long START_MIN_DELAY = 2000;      // 2 seconds minimum before start
const unsigned long START_MAX_DELAY = 5000;      // 5 seconds maximum before start
const unsigned long SAFETY_CAR_DURATION = 10000; // 10 seconds safety car period

class RaceManager {
private:
  RaceState currentState;
  int currentRedLight;
  unsigned long lastRedLightTime;
  unsigned long raceStartTime;
  unsigned long safetyCarStartTime;

  // State handlers
  void handleWaiting();
  void handleStartSequence();
  void handleRacing();
  void handleSafetyCar();
  void handleRaceStopped();

public:
  RaceManager();
  
  // Initialization
  void init();
  
  // Main update function (call in loop)
  void update();
  
  // Race control functions
  void startSequence();
  void startRace();
  void deploySafetyCar();
  void resumeRace();
  void stopRace();
  void resetSystem();
  
  // State query functions
  bool isWaiting() const;
  bool canDeploySafetyCar() const;
  RaceState getCurrentState() const;
};

// Global instance declaration
extern RaceManager race;

#endif