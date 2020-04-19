#include "PageFactory.h"

PageFactory::PageFactory(TFT_eSPI* display, RecodeApplicationService* recodeApp,
                         Config* config) {
  this->display = display;
  this->recodeApp = recodeApp;
  this->config = config;
}

std::unique_ptr<IPage> PageFactory::createPage(PageList page,
                                               IPageChange* changer) {
  switch (page) {
    case PageList::Main_p:
      return std::unique_ptr<IPage>(new MainPage(display, changer));
      break;
    case PageList::Select_p:
      return std::unique_ptr<IPage>(new SelectPage(display, changer));
    case PageList::Header_p:
      return std::unique_ptr<IPage>(new Header(display, changer));
      break;
    case PageList::Footer_p:
      return std::unique_ptr<IPage>(new Footer(display, changer));
    default:
      return nullptr;
  }
}
