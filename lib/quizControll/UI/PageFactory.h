#pragma once

#include <memory>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "IPage.h"
#include "IPageChange.h"
#include "PageList.h"
#include "TFT_eSPI.h"
#include "infrastructure/Button/ButtonInput.h"
// #include "UI/Page/MainPage.h"
#include "UI/Page/ConfigLimit.h"
#include "UI/Page/ConfigRecode.h"
#include "UI/Page/MainPage.h"
#include "UI/Page/MenuPage.h"

class PageFactory {
 public:
  PageFactory(TFT_eSPI* display, RecodeApplicationService* recodeApp,
              Config* config, ButtonInput* button);
  std::unique_ptr<IPage> create(PageList page, IPageChange* changer);

 protected:
  TFT_eSPI* display;
  RecodeApplicationService* recodeApp;
  Config* config;
  ButtonInput* button;
};