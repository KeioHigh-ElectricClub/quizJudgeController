#include "PageFactory.h"

PageFactory::PageFactory(TFT_eSPI* display, IPageChange* changer,
                         RecodeApplicationService* recodeApp, Config* config) {
  this->recodeApp = recodeApp;
  this->config = config;
}

std::unique_ptr<IPage> PageFactory::createPage(PageList list) {
  switch (list) {
    case Main_p:
      return std::unique_ptr<IPage>(
          new MainPage(display, changer, recodeApp, config));
      break;
    case Config_p:
      break;
    case Select_p:
      break;
  }
}