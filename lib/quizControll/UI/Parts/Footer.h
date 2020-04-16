#pragma once

#include <JC_Button.h>

#include "UI/IPage.h"

class Footer : public IPage {
 public:
  Footer(TFT_eSPI* display, IPageChange* changer);
  void init() override;
  void update() override;
  void draw() override;

  void setMessage(String left, String center, String right);
  bool isLeftPushed();
  bool isLeftPushedLong();
  bool isCenterPushed();
  bool isRightPushed();

 private:
  const uint8_t leftBtnPin = 32;
  const uint8_t centerBtnPin = 34;
  const uint8_t rightBtnPin = 35;

  bool isLeftPushedLongInternal = false;
  bool previousLeftPushedLong = false;
  bool isButtonPushed[3];

  Button btns[3];

  void initFrame();
  void initButton();
};