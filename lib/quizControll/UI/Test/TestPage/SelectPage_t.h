#pragma once

#include "TFT_eSPI.h"
#include "UI/IPage.h"
#include "UI/IPageChange.h"
class SelectPage : public IPage {
 public:
  SelectPage(TFT_eSPI* display, IPageChange* changer)
      : IPage(display, changer) {}
  void init() override { Serial.println("select init"); }
  void update() override { Serial.println("select update"); }
  void draw() override { Serial.println("select draw"); }
};
