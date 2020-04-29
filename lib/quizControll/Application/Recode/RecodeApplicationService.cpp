#include "Application/Recode/RecodeApplicationService.h"

RecodeApplicationService::RecodeApplicationService(
    IControllJudgeOutput& controller, IResultRepository& _resultRepository)
    : resultRepository(resultRepository), controller(controller) {}

void RecodeApplicationService::createAnswerRight(byte respondentNum,
                                                 byte waiting) {
  // if (nowRight != nullptr) return;
  nowRight = std::unique_ptr<AnswerRight>(new AnswerRight(respondentNum));
  this->waiting = waiting;
}
void RecodeApplicationService::showCorrect() {
  setErratum(Erratum::CORRECT);
  controller.softReset();
}
void RecodeApplicationService::showIncorrect() {
  setErratum(Erratum::INCORRECT);
  if (waiting <= 1)
    controller.softReset();
  else
    controller.assignRight();
}
void RecodeApplicationService::reset() {
  controller.softReset();
  if (canRecoding && nowRight != nullptr) {
    resultRepository.storeResetRecode();
  }
  nowRight.reset();
}
RecodeModel RecodeApplicationService::getRecode() {
  RecodeModel model;
  if (nowRight == nullptr) {
    model = RecodeModel();
  } else {
    model = RecodeModel(nowRight->getRespondentNum(), waiting);
  }
  return model;
}
void RecodeApplicationService::enableRecoding() {
  canRecoding = true;
  resultRepository.init();
}
void RecodeApplicationService::disableRecoding() { canRecoding = false; }
bool RecodeApplicationService::getCanRecoding() { return canRecoding; }

void RecodeApplicationService::setErratum(Erratum erratum) {
  if (nowRight == nullptr) return;
  nowRight->setErratum(erratum);

  if (canRecoding) {
    resultRepository.store(std::move(nowRight));
  }
  nowRight.reset();
}