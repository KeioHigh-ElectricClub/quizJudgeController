#include "AnswerRight.h"

bool AnswerRight::setErratum(Erratum _erratum) {
  if (_erratum == Erratum::HAVNT_ANSWERED) return false;
  erratum = _erratum;
  isAnswered = true;
  return true;
}

bool AnswerRight::getIsAnswered() { return isAnswered; }
