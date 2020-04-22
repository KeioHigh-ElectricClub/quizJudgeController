#pragma once

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IPage.h"

class Header : public IPage {
 public:
  Header(TFT_eSPI* display, IPageChange* changer,
         RecodeApplicationService* recodeApp, Config* config);
  void init() override;
  void update() override;
  void draw() override;

 private:
  RecodeApplicationService* recodeApp;
  Config* config;

  bool canRecode = false;
  Limit nowLimit = Limit::UNTIL1;
};