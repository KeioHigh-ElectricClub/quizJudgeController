#pragma once

#include <memory>

#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IPage.h"
#include "UI/Parts/Footer.h"
#include "infrastructure/Button/ButtonInput.h"

class MainPage : public IPage {
 public:
  MainPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button,
           RecodeApplicationService* recodeApp);

  void init() override;
  void update() override;
  void draw() override;

 private:
  RecodeApplicationService* recodeApp;
  ButtonInput* button;
  std::unique_ptr<Footer> footer;

  RecodeModel model;

  byte respondentNum = 0xff;
  byte waiting = 0;

  bool getData();
};