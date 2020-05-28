#pragma once

#include <memory>

#include "TFT_eSPI.h"

class IParts {
 public:
  IParts(TFT_eSPI* display) { this->display = display; }
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;

 protected:
  TFT_eSPI* display;
  bool mustUpdate;
};