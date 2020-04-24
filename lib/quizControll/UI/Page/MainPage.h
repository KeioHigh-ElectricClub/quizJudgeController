#pragma once

#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IPage.h"
#include "UI/Parts/Footer.h"

class MainPage : public IPage {
 public:
  MainPage(TFT_eSPI* display, IPageChange* changer,
           RecodeApplicationService* recodeApp, Footer* footer);

  void init() override;
  void update() override;
  void draw() override;

 private:
  RecodeApplicationService* recodeApp;
  Footer* footer;

  RecodeModel model;

  byte respondentNum = 0xff;
  byte waiting = 0;

  bool getData();
};