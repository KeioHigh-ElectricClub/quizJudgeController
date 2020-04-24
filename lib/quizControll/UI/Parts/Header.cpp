#include "Header.h"

Header::Header(TFT_eSPI* display, IPageChange* changer,
               RecodeApplicationService* recodeApp, Config* config)
    : IPage(display, changer) {
  this->recodeApp = recodeApp;
  this->config = config;
}

void Header::init() {
  uint32_t frameColor = display->color24to16(0x707070);
  display->drawFastHLine(0, 36, 320, frameColor);
  display->drawFastVLine(176, 0, 36, frameColor);

  display->setTextDatum(TL_DATUM);
  display->setCursor(286, 16);
  display->drawString("まで", 186, 16);

  canRecode = recodeApp->getCanRecoding();
  nowLimit = config->getLimit();
  draw();
}

void Header::update() {
  bool canRecodeTmp = canRecode;
  Limit nowLimitTmp = nowLimit;
  canRecode = recodeApp->getCanRecoding();
  nowLimit = config->getLimit();

  if (canRecode != canRecodeTmp && nowLimit != nowLimitTmp) mustUpdate = true;
}

void Header::draw() {
  if (!mustUpdate) return;

  String recoding;
  if (canRecode) {
    recoding = "記録ON";
    display->setTextColor(TFT_RED, TFT_WHITE);
  } else {
    recoding = "記録OFF";
    display->setTextColor(TFT_BLACK, TFT_WHITE);
  }
  display->setTextDatum(TC_DATUM);
  display->setTextPadding(78);
  display->drawString(recoding, 197, 6);

  String limit;
  switch (nowLimit) {
    case Limit::UNTIL1:
      limit = "1位";
      break;
    case Limit::UNTIL2:
      limit = "2位";
      break;
    case Limit::UNTIL20:
      limit = "20位";
      break;
  }

  display->setTextDatum(TL_DATUM);
  display->setTextPadding(42);
  display->setTextColor(TFT_BLACK, TFT_WHITE);
  display->drawString(limit, 285, 6);

  mustUpdate = false;
}