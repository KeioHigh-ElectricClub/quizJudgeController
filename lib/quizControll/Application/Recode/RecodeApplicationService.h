#pragma once

#include <Arduino.h>

#include <memory>

#include "Application/Recode/DummyRepository.h"
#include "Application/Recode/IControllJudgeOutput.h"
#include "Application/Recode/RecodeModel.h"
#include "domain/Recode/AnswerRight.h"
#include "domain/Recode/Erratum.h"
#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Result.h"

class RecodeApplicationService {
 public:
  RecodeApplicationService(IControllJudgeOutput* controller,
                           IResultRepository* _resultRepository);
  ~RecodeApplicationService() {}

  void createAnswerRight(byte respondentNum, byte waiting);
  void showCorrect();
  void showIncorrect();
  void reset();
  RecodeModel getRecode();

  void enableRecoding();
  void disableRecoding();
  bool getCanRecoding();

 private:
  bool isRecoding = false;
  byte waiting;
  std::unique_ptr<AnswerRight> nowRight = nullptr;
  IResultRepository* resultRepository = nullptr;
  IControllJudgeOutput* controller = nullptr;
  bool canRecoding = false;

  void setErratum(Erratum erratum);
};