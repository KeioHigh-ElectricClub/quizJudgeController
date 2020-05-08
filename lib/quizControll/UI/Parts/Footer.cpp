#include "Footer.h"

Footer::Footer(TFT_eSPI* display, ButtonInput* button) {
  this->button = button;
  this->display = display;
}

void Footer::init() {
  uint32_t frameColor = display->color24to16(0x707070);
  display->drawFastHLine(0, 200, 320, frameColor);
  display->drawFastVLine(106, 200, 40, frameColor);
  display->drawFastVLine(214, 200, 40, frameColor);
}

void Footer::setMessage(String left, String center, String right) {
  display->loadFont("YuGothic20");
  display->setCursor(53, 208);
  display->setTextDatum(TC_DATUM);
  display->drawString(left, 53, 208);

  display->setCursor(160, 208);
  display->drawString(center, 160, 208);

  display->setCursor(267, 208);
  display->drawString(right, 267, 208);
  display->unloadFont();
}