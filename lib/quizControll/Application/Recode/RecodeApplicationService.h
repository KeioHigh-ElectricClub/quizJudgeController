#pragma once

#include <Arduino.h>
#include <memory>

#include "domain/Recode/AnswerRight.h"
#include "domain/Recode/Erratum.h"
#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Result.h"

#include "Application/Recode/IControllJudgeOutput.h"
#include "Application/Recode/RecodeModel.h"

class RecodeApplicationService {
 public:
  RecodeApplicationService(IControllJudgeOutput* controller);
  RecodeApplicationService(IControllJudgeOutput* controller,
                           IResultRepository* _resultRepository);
  ~RecodeApplicationService() {}

  void createAnswerRight(byte respondentNum, byte waiting);
  void showCorrect();
  void showIncorrect();
  void reset();
  RecodeModel getRecode();

  void setIsRecoding(bool isRecoding);
  bool getIsRecoding();

 private:
  bool isRecoding = false;
  byte waiting;
  std::unique_ptr<AnswerRight> nowRight = nullptr;
  IResultRepository* resultRepository = nullptr;
  IControllJudgeOutput* controller = nullptr;

  void setErratum(Erratum erratum);
};