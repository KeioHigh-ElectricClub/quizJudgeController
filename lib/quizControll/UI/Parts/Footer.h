#pragma once

#include <JC_Button.h>

#include "TFT_eSPI.h"
#include "infrastructure/Button/ButtonInput.h"

class Footer {
 public:
  Footer(TFT_eSPI* display, ButtonInput* button);
  void init();
  void update();
  void draw();

  void setMessage(String left, String center, String right);

 private:
  ButtonInput* button;
  TFT_eSPI* display;
};