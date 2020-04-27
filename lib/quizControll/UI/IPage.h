#pragma once

#include <memory>

#include "IPageChange.h"
#include "TFT_eSPI.h"
#include "UI/Parts/Footer.h"
#include "infrastructure/Button/ButtonInput.h"

class IPage {
 public:
  IPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button) {
    this->display = display;
    this->changer = changer;
    this->button = button;
    footer = std::unique_ptr<Footer>(new Footer(display, button));
  }
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;

 protected:
  TFT_eSPI* display;
  IPageChange* changer;
  ButtonInput* button;
  std::unique_ptr<Footer> footer;
  bool mustUpdate;
};