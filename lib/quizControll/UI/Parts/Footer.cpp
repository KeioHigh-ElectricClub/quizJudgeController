#include "Footer.h"

Footer::Footer(TFT_eSPI* display, IPageChange* changer)
    : IPage(display, changer), btns{leftBtnPin, centerBtnPin, rightBtnPin} {}

void Footer::init() {
  initFrame();
  initButton();
}

void Footer::initFrame() {
  uint32_t frameColor = display->color24to16(0x707070);
  display->drawFastHLine(0, 200, 320, frameColor);
  display->drawFastVLine(106, 200, 40, frameColor);
  display->drawFastVLine(214, 200, 40, frameColor);
}

void Footer::initButton() {
  for (auto btn : btns) {
    btn.begin();
  }
}

void Footer::update() {
  for (auto btn : btns) {
    btn.read();
  }
  if (btns[0].pressedFor(1000)) {
    isLeftPushedLongInternal = true;
    previousLeftPushedLong = true;
  } else if (btns[0].wasReleased()) {
    if (previousLeftPushedLong) {
      previousLeftPushedLong = false;
      return;
    }
    isButtonPushed[0] = true;
    return;
  }
  if (btns[1].wasReleased()) {
    isButtonPushed[1] = true;
    return;
  }
  if (btns[2].wasReleased()) {
    isButtonPushed[2] = true;
    return;
  }
}
bool Footer::isLeftPushed() { return isButtonPushed[0]; }
bool Footer::isLeftPushedLong() { return isLeftPushedLong; }
bool Footer::isCenterPushed() { return isButtonPushed[1]; }
bool Footer::isRightPushed() { return isButtonPushed[2]; }

void Footer::draw() {}

void Footer::setMessage(String left, String center, String right) {
  display->setCursor(53, 208);
  display->setTextDatum(TC_DATUM);
  display->print(left);

  display->setCursor(160, 208);
  display->print(center);

  display->setCursor(267, 208);
  display->print(right);
}