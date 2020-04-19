#pragma once

#include "TFT_eSPI.h"
#include "UI/IPage.h"
#include "UI/IPageChange.h"

class Footer : public IPage {
 public:
  Footer(TFT_eSPI* display, IPageChange* changer) : IPage(display, changer) {
    Serial.println("Hoge");
  }
  void init() { Serial.println("Footer init"); }
  void update() { Serial.println("Footer update"); }
  void draw() { Serial.println("Footer draw"); }
};