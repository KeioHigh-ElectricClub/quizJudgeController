#include "PageManager.h"

PageManager::PageManager(PageFactory* pageFactory, PartsFactory* partsFactory,
                         TFT_eSPI* display) {
  this->pageFactory = pageFactory;
  this->partsFactory = partsFactory;
  this->display = display;
}

void PageManager::init() {
  header = partsFactory->createPage(PartsList::Header);
  if (header == nullptr) throw "Failed to initialize Header";
  nowPage = pageFactory->createPage(PageList::Main_p, this);
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
  nowPage = pageFactory->createPage(nextPage, this);
  if (nowPage == nullptr)
    nowPage = pageFactory->createPage(PageList::Main_p, this);
  nowPage->init();
  nowPage->update();
}
