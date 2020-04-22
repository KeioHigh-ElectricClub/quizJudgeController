#pragma once

#include "IPageChange.h"
#include "TFT_eSPI.h"

class IPage {
 public:
  IPage(TFT_eSPI* display, IPageChange* changer) {
    this->display = display;
    this->changer = changer;
  }
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;

 protected:
  TFT_eSPI* display;
  IPageChange* changer;
  bool mustUpdate;
};