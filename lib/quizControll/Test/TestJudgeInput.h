#pragma once

#include <Arduino.h>
#include <JC_Button.h>
#include <Wire.h>

#include "Application/Recode/RecodeApplicationService.h"
#include "infrastructure/Sound/Sound.h"

class TestJudgeInput {
 public:
  TestJudgeInput(byte inputPin, RecodeApplicationService& recodeApp)
      : recodeApp(recodeApp), button(inputPin) {}

  void begin() { button.begin(); }
  void update() {
    button.read();
    if (!button.wasReleased()) return;
    recodeApp.createAnswerRight(random(0, 20), random(0, 20));
  }

 private:
  RecodeApplicationService& recodeApp;
  Button button;
  byte receive(byte select);
  bool send(byte select);
};