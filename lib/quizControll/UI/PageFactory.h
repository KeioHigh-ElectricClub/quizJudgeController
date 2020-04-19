#pragma once

#include <memory>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "IPage.h"
#include "IPageChange.h"
#include "PageList.h"
#include "TFT_eSPI.h"
// #include "UI/Page/MainPage.h"
#include "UI/Test/TestPage/MainPage_t.h"
#include "UI/Test/TestPage/SelectPage_t.h"
#include "UI/Test/TestParts/Footer_t.h"
#include "UI/Test/TestParts/Header_t.h"

class PageFactory {
 public:
  PageFactory(TFT_eSPI* display, RecodeApplicationService* recodeApp,
              Config* config);
  std::unique_ptr<IPage> createPage(PageList page, IPageChange* changer);

 protected:
  TFT_eSPI* display;
  RecodeApplicationService* recodeApp;
  Config* config;
};