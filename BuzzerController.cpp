#include "BuzzerController.h"
#define BUZZER_PIN 25

void BuzzerController::begin() {
    pinMode(BUZZER_PIN, OUTPUT);
    buzzerState = "Off";
}

void BuzzerController::setState(String state) {
    buzzerState = state;
    apply();
}

void BuzzerController::apply() {
    digitalWrite(BUZZER_PIN, buzzerState == "On" ? HIGH : LOW);
}

String BuzzerController::getState(){
  return buzzerState;
}