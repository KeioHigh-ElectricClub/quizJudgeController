#pragma once

#include "TFT_eSPI.h"
#include "UI/IPage.h"
#include "UI/IPageChange.h"
class MainPage : public IPage {
 public:
  MainPage(TFT_eSPI* display, IPageChange* changer) : IPage(display, changer) {}
  void init() override { Serial.println("main init"); }
  void update() override {
    Serial.println("main update");
    changer->changePage(PageList::Select_p);
  }
  void draw() override { Serial.println("main draw"); }
};
