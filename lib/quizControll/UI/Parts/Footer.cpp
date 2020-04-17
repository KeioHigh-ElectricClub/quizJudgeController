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

void Footer::setEnableLongPush(bool left, bool center, bool right) {
  isEnableLongPush[0] = left;
  isEnableLongPush[1] = center;
  isEnableLongPush[2] = right;
}

void Footer::update() {
  for (byte i = 0; i < sizeof(btns) / sizeof(btns[0]); i++) {
    btns[i].read();
    if (isEnableLongPush[i] && btns[i].pressedFor(1000)) {
      isButtonLongPushed[i] = true;
      previousButtonPushedLong[i] = true;
    } else if (btns[i].wasReleased()) {
      if (previousButtonPushedLong[i]) {
        previousButtonPushedLong[i] = false;
        return;
      }
      isButtonPushed[i] = true;
      return;
    }
  }
}

bool Footer::isButtonPushedInternal(byte num) {
  bool temp = isButtonPushed[num];
  isButtonPushed[num] = false;
  return temp;
}
bool Footer::isButtonPushedLongInternal(byte num) {
  bool temp = isButtonLongPushed[num];
  isButtonLongPushed[num] = false;
  return temp;
}

bool Footer::isLeftPushed() { return isButtonPushedInternal(0); }
bool Footer::isLeftPushedLong() { return isButtonPushedLongInternal(0); }
bool Footer::isCenterPushed() { return isButtonPushedInternal(1); }
bool Footer::isRightPushed() { return isButtonPushedInternal(2); }

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