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
  void setEnableLongPush(bool left, bool center, bool right);
  bool isLeftPushed();
  bool isLeftPushedLong();
  bool isCenterPushed();
  bool isRightPushed();

 private:
  const uint8_t leftBtnPin = 32;
  const uint8_t centerBtnPin = 34;
  const uint8_t rightBtnPin = 35;

  bool isButtonLongPushed[3];
  bool prevPagePushedButton[3];
  bool prevPushedButtonLong[3];
  bool isButtonPushed[3];
  bool isEnableLongPush[3];

  Button btns[3];

  bool isButtonPushedInternal(byte num);
  bool isButtonPushedLongInternal(byte num);

  void initFrame();
  void initButton();
};