#pragma once

#include <Arduino.h>
#include <memory>
#include "Recode.h"

class Result : public Recode {
 public:
  Result(std::shared_ptr<Recode> recode) {
    respondentNum = recode->getRespondentNum();
    erratum = recode->getErratum();
  }
};
