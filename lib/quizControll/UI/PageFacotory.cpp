#include "PageFactory.h"

PageFactory::PageFactory(TFT_eSPI* display, RecodeApplicationService* recodeApp,
                         Config* config, ButtonInput* button) {
  this->display = display;
  this->recodeApp = recodeApp;
  this->config = config;
  this->button = button;
}

std::unique_ptr<IPage> PageFactory::createPage(PageList page,
                                               IPageChange* changer) {
  switch (page) {
    case PageList::Main_p:
      return std::unique_ptr<IPage>(
          new MainPage(display, changer, button, recodeApp));
      break;
    case PageList::Menu_p:
      return std::unique_ptr<IPage>(new MenuPage(display, changer, button));
    default:
      return nullptr;
  }
}
