#pragma once

#include <Arduino.h>
#include "Erratum.h"

class Recode {
 public:
  Recode() {}
  Recode(byte _respondentNum) { respondentNum = _respondentNum; }
  virtual ~Recode() {}

  byte getRespondentNum() { return respondentNum; }
  Erratum getErratum() { return erratum; }

 protected:
  byte respondentNum = 0xFF;
  Erratum erratum = Erratum::HAVNT_ANSWERED;
};