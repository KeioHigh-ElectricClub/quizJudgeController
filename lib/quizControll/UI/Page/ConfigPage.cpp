#include "ConfigPage.h"

ConfigPage::ConfigPage(TFT_eSPI* display, IPageChange* changer,
                       ButtonInput* button, RecodeApplicationService* recodeApp)
    : IPage(display, changer, button) {
  this->recodeApp = recodeApp;
}
void ConfigPage::init() {
  display->fillRect(0, 37, 320, 163, TFT_WHITE);
  button->init();
  button->setEnableLongPush(false, false, false);
  footer->init();
  footer->setMessage("決定", "<", ">");
  mustUpdate = true;
  draw();
}
void ConfigPage::update() {
  button->update();

  if (button->isLeftPushed()) {
    items[positionIndex].func();
    return;
  }
  if (button->isCenterPushed()) {
    mustUpdate = true;
    if (positionIndex <= 0) {
      positionIndex = 0;
      return;
    }
    positionIndex--;
  }
  if (button->isRightPushed()) {
    mustUpdate = true;
    if (positionIndex >= items.size() - 1) {
      positionIndex = items.size() - 1;
      return;
    }
    positionIndex++;
  }
  // Serial.printf("position: %d\n", positionIndex);
}

void ConfigPage::draw() {
  if (!mustUpdate) return;

  const int frameColor = display->color24to16(0x707070);
  const int selectColor = display->color24to16(0x707070);
  const int fillColor = display->color24to16(0xf3f3f3);

  display->loadFont("YuGothic20");
  for (byte i = 0; i < items.size(); i++) {
    int xpos = rowXpos[i % 2];
    int ypos = colomnYpos[i / 2];

    display->fillRect(xpos + 1, ypos + 1, itemWidth - 2, itemHeight - 2,
                      fillColor);
    display->drawRect(xpos, ypos, itemWidth, itemHeight,
                      (i == positionIndex) ? TFT_RED : frameColor);
    display->setTextDatum(CC_DATUM);
    display->setTextColor(TFT_BLACK);
    display->drawString(items[i].name, xpos + itemWidth / 2,
                        ypos + itemHeight / 2);
  }
  display->unloadFont();

  mustUpdate = false;
}
void ConfigPage::drawTitle(String title) {
  display->loadFont("YuGothic20");
  display->setTextDatum(TL_DATUM);
  display->drawString(title, 10, 43);
  display->unloadFont();
}