#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "Application/Config/IConfigOutput.h"
#include "Application/Recode/IControllJudgeOutput.h"

class JudgeOutput : public IConfigOutput, public IControllJudgeOutput {
 public:
  JudgeOutput(byte sda, byte scl);

  bool setLimit(Limit limit);
  bool assignRight();
  bool softReset();

 private:
  bool send(byte select);
  bool send(byte select, byte data);
};