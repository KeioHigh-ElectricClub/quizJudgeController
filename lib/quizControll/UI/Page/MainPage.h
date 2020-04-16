#pragma once

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IPage.h"

class MainPage : public IPage {
 public:
  MainPage(TFT_eSPI* display, IPageChange* changer,
           RecodeApplicationService* recodeApp, Config* config);

  void init() override;
  void update() override;
  void draw() override;
};