#include "ConfigLimit.h"

ConfigLimit::ConfigLimit(TFT_eSPI* display, IPageChange* changer,
                         ButtonInput* button,
                         RecodeApplicationService* recodeApp, Config* config)
    : ConfigPage(display, changer, button, recodeApp) {
  this->config = config;

  items.push_back({"1位", [this]() {
                     this->config->setLimit(Limit::UNTIL1);
                     this->changer->changePage(PageList::Main);
                     this->recodeApp->reset();
                   }});
  items.push_back({"2位", [this]() {
                     this->config->setLimit(Limit::UNTIL2);
                     this->changer->changePage(PageList::Main);
                     this->recodeApp->reset();
                   }});
  items.push_back({"20位", [this]() {
                     this->config->setLimit(Limit::UNTIL20);
                     this->changer->changePage(PageList::Main);
                     this->recodeApp->reset();
                   }});
  items.push_back(
      {"戻る", [this]() { this->changer->changePage(PageList::Menu); }});
}

void ConfigLimit::init() {
  display->fillRect(37, 0, 320, 163, TFT_WHITE);
  ConfigPage::init();
  drawTitle("判定人数");
}
void ConfigLimit::update() { ConfigPage::update(); }
void ConfigLimit::draw() { ConfigPage::draw(); }