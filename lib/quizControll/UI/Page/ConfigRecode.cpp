#include "ConfigRecode.h"

ConfigRecode::ConfigRecode(TFT_eSPI* display, IPageChange* changer,
                           ButtonInput* button,
                           RecodeApplicationService* recodeApp)
    : ConfigPage(display, changer, button, recodeApp) {
  items.push_back({"ON", [this]() {
                     this->recodeApp->enableRecoding();
                     this->changer->changePage(PageList::Main);
                     this->recodeApp->reset();
                   }});
  items.push_back({"OFF", [this]() {
                     this->recodeApp->disableRecoding();
                     this->changer->changePage(PageList::Main);
                     this->recodeApp->reset();
                   }});
  items.push_back(
      {"戻る", [this]() { this->changer->changePage(PageList::Menu); }});
}

void ConfigRecode::init() {
  ConfigPage::init();
  drawTitle("記録");
}
void ConfigRecode::update() { ConfigPage::update(); }
void ConfigRecode::draw() { ConfigPage::draw(); }