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
  footer->setMessage("決定", "<", ">");
  button->setEnableLongPush(false, false, false);

  display->fillRect(0, 37, 320, 163, TFT_WHITE);

  items[0][0] = {"戻る", [this]() { changer->changePage(PageList::Main); }};
  items[0][1] = {"人数",
                 [this]() { changer->changePage(PageList::ConfigLimit); }};
  items[1][0] = {"記録",
                 [this]() { changer->changePage(PageList::ConfigRecode); }};
  items[1][1] = {ignoreItem, []() {}};

  draw();
}

void MenuPage::update() {
  Serial.println("menu update");
  button->update();

  if (button->isLeftPushed()) {
    Serial.println("left pushed");
    onLeftPushed();
    mustUpdate = true;
    return;
  }
  if (button->isCenterPushed()) {
    Serial.println("center pushed");
    onCenterPushed();
    mustUpdate = true;
    return;
  }
  if (button->isRightPushed()) {
    Serial.println("right pushed");
    onRightPushed();
    mustUpdate = true;
    return;
  }
  Serial.println("menu update end");
  Serial.printf("position: %d, page: %d\n", positionIndex, pageIndex);
}

void MenuPage::onLeftPushed() {
  if (positionIndex == -1) {
    if (pageIndex == 0) {
      positionIndex = 0;
      return;
    };
    pageIndex--;
    positionIndex = 2;
    return;
  } else if (positionIndex == 2) {
    if (pageIndex == MAX_PAGE - 1) {
      positionIndex = 0;
      return;
    }
    pageIndex++;
    positionIndex = 0;
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
  Serial.println("draw");
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
    display->drawString(items[pageIndex][i].name, posX + 52, 120);
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
  mustUpdate = false;
}

uint32_t MenuPage::frameColor(int positionIndexA) {
  return (this->positionIndex == positionIndexA)
             ? TFT_RED
             : display->color24to16(0x707070);
}