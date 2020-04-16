#include "PageManager.h"

PageManager::PageManager(PageFactory* factory) { this->factory = factory; }
void PageManager::update() { nowPage->update(); }
void PageManager::draw() { nowPage->draw(); }
void PageManager::changePage(PageList nextPage) {
  nowPage = factory->createPage(nextPage);
  nowPage->init();
}