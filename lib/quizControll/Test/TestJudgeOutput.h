#pragma once

#include <Arduino.h>

#include "Application/Config/IConfigOutput.h"
#include "Application/Recode/IControllJudgeOutput.h"
#include "domain/Config/Limit.h"

class TestJudgeOutput : public IConfigOutput, public IControllJudgeOutput {
 public:
  TestJudgeOutput() {}
  ~TestJudgeOutput() {}

  bool softReset() {
    Serial.println("Soft Reset");
    return true;
  }
  bool setLimit(Limit limit) {
    switch (limit) {
      case Limit::UNTIL1:
        Serial.println("UNTIL1");
        break;
      case Limit::UNTIL2:
        Serial.println("UNTIL2");
        break;
      case Limit::UNTIL20:
        Serial.println("UNTIL20");
        break;
    }
    return true;
  }
  bool assignRight() {
    Serial.println("AssignRight");
    return true;
  }
};