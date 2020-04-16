#pragma once

#include <memory>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "IPageChange.h"
#include "PageList.h"
#include "TFT_eSPI.h"
#include "UI/IPage.h"
#include "UI/Page/MainPage.h"

class PageFactory {
 public:
  PageFactory(TFT_eSPI* display, IPageChange* changer,
              RecodeApplicationService* recodeApp, Config* config) {
    this->display = display;
    this->changer = changer;
    this->recodeApp = recodeApp;
    this->config = config;
  }
  std::unique_ptr<IPage> createPage(PageList page);

 private:
  TFT_eSPI* display;
  IPageChange* changer;
  RecodeApplicationService* recodeApp;
  Config* config;
}