#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "Application/Recode/RecodeApplicationService.h"

class JudgeInput {
 public:
  JudgeInput(byte sda, byte scl, RecodeApplicationService& recodeApp);

  void begin();
  void update();

 private:
  RecodeApplicationService& recodeApp;
  byte receive(byte select);
  bool send(byte select);
};