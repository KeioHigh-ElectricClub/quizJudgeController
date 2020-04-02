#include "Application/Recode/RecodeApplicationService.h"

RecodeApplicationService::RecodeApplicationService(
    IControllJudgeOutput* controller) {
  if (controller == nullptr) throw "set controller";
  this->controller = controller;
}
RecodeApplicationService::RecodeApplicationService(
    IControllJudgeOutput* controller, IResultRepository* _resultRepository)
    : RecodeApplicationService(controller) {
  if (_resultRepository == nullptr) return;
  isRecoding = true;
  resultRepository = _resultRepository;
}

void RecodeApplicationService::createAnswerRight(byte respondentNum,
                                                 byte waiting) {
  if (nowRight != nullptr) return;
  nowRight = std::unique_ptr<AnswerRight>(new AnswerRight(respondentNum));
  this->waiting = waiting;
}
void RecodeApplicationService::showCorrect() {
  setErratum(Erratum::CORRECT);
  controller->softReset();
}
void RecodeApplicationService::showIncorrect() {
  setErratum(Erratum::INCORRECT);
  if (waiting <= 1)
    controller->softReset();
  else
    controller->assignRight();
}
void RecodeApplicationService::reset() { nowRight.reset(); }
RecodeModel RecodeApplicationService::getRecode() {
  RecodeModel model;
  if (nowRight == nullptr) {
    model = RecodeModel();
  } else {
    model = RecodeModel(nowRight->getRespondentNum());
  }
  return model;
}
void RecodeApplicationService::setIsRecoding(bool isRecoding) {
  this->isRecoding = isRecoding;
  if (this->isRecoding) resultRepository->init();
}
bool RecodeApplicationService::getIsRecoding() { return isRecoding; }

void RecodeApplicationService::setErratum(Erratum erratum) {
  if (nowRight == nullptr) return;
  nowRight->setErratum(erratum);
  if (!isRecoding) return;

  resultRepository->store(std::move(nowRight));
  nowRight.reset();
}