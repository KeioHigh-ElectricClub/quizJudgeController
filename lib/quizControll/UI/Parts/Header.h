#pragma once

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IParts.h"

class Header : public IParts {
 public:
  Header(TFT_eSPI* display, RecodeApplicationService* recodeApp,
         Config* config);
  void init() override;
  void update() override;
  void draw() override;

 private:
  RecodeApplicationService* recodeApp;
  Config* config;

  bool canRecode = false;
  Limit nowLimit = Limit::UNTIL1;
};