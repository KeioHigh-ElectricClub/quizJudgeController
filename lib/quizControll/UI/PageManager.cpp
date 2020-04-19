#include "PageManager.h"

PageManager::PageManager(PageFactory* factory) { this->factory = factory; }

void PageManager::init() {
  header = factory->createPage(PageList::Header_p, this);
  if (header == nullptr) throw "Failed to initialize Header";
  footer = factory->createPage(PageList::Footer_p, this);
  if (footer == nullptr) throw "Failed to initialize Footer";
  nowPage = factory->createPage(PageList::Main_p, this);
  if (nowPage == nullptr) throw "Failed to initialize main";
  header->init();
  footer->init();
  nowPage->init();
}
void PageManager::update() {
  header->update();
  footer->update();

  nowPage->update();
}
void PageManager::draw() {
  header->draw();
  footer->draw();
  nowPage->draw();
}
void PageManager::changePage(PageList nextPage) {
  nowPage = factory->createPage(nextPage, this);
  if (nowPage == nullptr) nowPage = factory->createPage(PageList::Main_p, this);
  nowPage->init();
  nowPage->update();
}