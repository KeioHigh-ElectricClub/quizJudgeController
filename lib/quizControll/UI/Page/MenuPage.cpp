#include "MenuPage.h"

// 左側ページ戻り三角→-1
// 左アイテム→0
// 右アイテム→1
// 右側ページ送り三角→2

MenuPage::MenuPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button)
    : IPage(display, changer, button) {
  Serial.println("MenuPage constructor");
}

void MenuPage::init() {
  button->init();
  footer->setMessage("決定", "◀", "▶");
  button->setEnableLongPush(false, false, false);

  items[0][0] = {"戻る", [this]() { changer->changePage(PageList::Main); }};
  items[0][1] = {"判定\n人数",
                 [this]() { changer->changePage(PageList::ConfigLimit); }};
  items[1][0] = {"記録",
                 [this]() { changer->changePage(PageList::ConfigRecode); }};
  items[1][1] = {ignoreItem, []() {}};

  display->fillRect(37, 0, 162, 320, TFT_WHITE);

  draw();
}

void MenuPage::update() {
  if (button->isLeftPushed()) {
    onLeftPushed();
    mustUpdate = true;
    return;
  }
  if (button->isCenterPushed()) {
    onCenterPushed();
    mustUpdate = true;
    return;
  }
  if (button->isRightPushed()) {
    onRightPushed();
    mustUpdate = true;
    return;
  }
}

void MenuPage::onLeftPushed() {
  if (positionIndex == -1) {
    if (pageIndex == 0) {
      positionIndex = 0;
      return;
    };
    pageIndex--;
    return;
  } else if (positionIndex == 2) {
    if (pageIndex == MAX_PAGE - 1) {
      positionIndex = 0;
      return;
    }
    pageIndex++;
    return;
  }
  if (items[pageIndex][positionIndex].name == ignoreItem) {
    positionIndex = 0;
    return;
  }
  items[pageIndex][positionIndex].func();
  return;
}
void MenuPage::onCenterPushed() {
  if (positionIndex == -1 || (pageIndex == 0 && positionIndex == 0)) return;
  positionIndex--;
  return;
}
void MenuPage::onRightPushed() {
  if (positionIndex == 2) return;
  bool isLastIgnore = items[MAX_PAGE - 1][1].name == ignoreItem;
  if (pageIndex == MAX_PAGE - 1 && (positionIndex == 1 || isLastIgnore)) return;

  positionIndex++;
  return;
}

void MenuPage::draw() {
  if (!mustUpdate) return;

  display->loadFont("YuGothic20");

  for (int i = 0; i < 2; i++) {
    if (items[pageIndex][i].name == ignoreItem) continue;

    int posX = (i == 0) ? 47 : 169;
    display->fillRect(posX + 1, 68 + 1, 102, 102,
                      display->color24to16(0xf3f3f3));

    uint32_t color = frameColor(i);
    display->drawRect(posX, 68, 104, 104, color);

    display->setTextDatum(CC_DATUM);
    display->setTextColor(TFT_BLACK);
    display->drawString(items[pageIndex][i].name, 99, 120);
  }
  display->unloadFont();

  if (pageIndex != 0) {
    uint32_t triangleColor = frameColor(-1);
    display->drawTriangle(9, 120, 39, 135, 39, 105, triangleColor);
  }
  if (pageIndex != MAX_PAGE - 1) {
    uint32_t triangleColor = frameColor(2);
    display->drawTriangle(291, 105, 317, 120, 291, 135, triangleColor);
  }
}

uint32_t MenuPage::frameColor(int postionIndex) {
  return (this->positionIndex == positionIndex)
             ? TFT_RED
             : display->color24to16(0x707070);
}