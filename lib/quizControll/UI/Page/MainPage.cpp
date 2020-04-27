#include "MainPage.h"

MainPage::MainPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button,
                   RecodeApplicationService* recodeApp)
    : IPage(display, changer, button) {
  this->recodeApp = recodeApp;
}

void MainPage::init() {
  button->init();
  button->setEnableLongPush(true, false, false);
  footer->setMessage("リセット", "不正解", "正解");

  display->loadFont("YuGothic20");

  display->setTextDatum(TC_DATUM);
  display->drawString("人　回答中", 197, 61);

  display->setCursor(45, 151);
  display->drawString("回答中", 45, 151);

  display->drawString("番", 120, 118);

  display->unloadFont();

  display->loadFont("YuGothic12");
  display->drawString("リセット長押しでメニュー", 168, 173);
  display->unloadFont();

  getData();
  mustUpdate = true;
  draw();
}
void MainPage::update() {
  if (button->isLeftPushedLong()) {
    changer->changePage(PageList::Menu_p);
  }
  if (button->isLeftPushed()) {
    recodeApp->reset();
  }
  if (button->isCenterPushed()) {
    recodeApp->showIncorrect();
  }
  if (button->isRightPushed()) {
    recodeApp->showCorrect();
  }

  mustUpdate = getData();
}
void MainPage::draw() {
  if (!mustUpdate) return;

  display->loadFont("YuGothic80");
  display->setTextDatum(TC_DATUM);
  display->setTextColor(TFT_BLACK, TFT_WHITE);
  display->setTextPadding(88);
  if (respondentNum == 0xff) {
    display->drawChar('-', 75, 61);
  } else {
    display->drawNumber(respondentNum, 75, 61);
  }
  display->unloadFont();

  display->loadFont("YuGothic20");
  display->setTextDatum(TR_DATUM);
  display->setTextPadding(22);
  display->drawNumber(waiting, 196, 61);
  display->unloadFont();

  mustUpdate = false;
}

bool MainPage::getData() {
  byte respondentNum = this->respondentNum;
  byte waiting = this->waiting;

  this->model = recodeApp->getRecode();
  this->respondentNum =
      (model.getExistsRight()) ? model.getRespondentNum() : 0xff;
  this->waiting = model.getWainting();

  if (this->respondentNum != respondentNum || this->waiting != waiting)
    return true;
  return false;
}