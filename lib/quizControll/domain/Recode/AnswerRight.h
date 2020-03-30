#pragma once

#include <Arduino.h>

#include <memory>
#include "Erratum.h"
#include "Recode.h"

class AnswerRight : public Recode {
 public:
  AnswerRight(byte _respondentNum) : Recode(_respondentNum) {}
  ~AnswerRight() {}

  bool getIsAnswered();

  bool setErratum(Erratum _erratum);

 private:
  bool isAnswered = false;
};
