#include "PageManager.h"

PageManager::PageManager(PageFactory& pageFactory, PartsFactory& partsFactory,
                         TFT_eSPI* display)
    : pageFactory(pageFactory), partsFactory(partsFactory) {
  this->display = display;
}

void PageManager::init() {
  display->fillScreen(TFT_WHITE);
  header = partsFactory.create(PartsList::Header);
  if (header == nullptr) throw "Failed to initialize Header";
  nowPage = pageFactory.create(PageList::Main, this);
  if (nowPage == nullptr) throw "Failed to initialize main";

  header->init();
  nowPage->init();
}
void PageManager::update() {
  header->update();
  nowPage->update();
}
void PageManager::draw() {
  header->draw();
  nowPage->draw();
}
void PageManager::changePage(PageList nextPage) {
  nowPage = pageFactory.create(nextPage, this);
  if (nowPage == nullptr) {
    nowPage = pageFactory.create(PageList::Main, this);
    Serial.println("error invalid page");
  }
  nowPage->init();
  nowPage->update();
}
