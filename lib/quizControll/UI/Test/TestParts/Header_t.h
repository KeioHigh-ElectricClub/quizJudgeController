#pragma once

#include "TFT_eSPI.h"
#include "UI/IPage.h"
#include "UI/IPageChange.h"

class Header : public IPage {
 public:
  Header(TFT_eSPI* display, IPageChange* changer) : IPage(display, changer) {}
  void init() { Serial.println("Header init"); }
  void update() { Serial.println("Header update"); }
  void draw() { Serial.println("Header draw"); }
};