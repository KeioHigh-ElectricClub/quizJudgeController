#pragma once

#include <JC_Button.h>

class ButtonInput {
 public:
  ButtonInput();
  ~ButtonInput() {}

  void update();

  void setEnableLongPush(bool left, bool center, bool right);
  bool isLeftPushed();
  bool isLeftPushedLong();
  bool isCenterPushed();
  bool isRightPushed();
  void init();

 private:
  const uint8_t leftBtnPin = 32;
  const uint8_t centerBtnPin = 34;
  const uint8_t rightBtnPin = 35;

  bool isButtonLongPushed[3]{0};
  bool prevPagePushedButton[3]{0};
  bool prevPushedButtonLong[3]{0};
  bool isButtonPushed[3]{0};
  bool isEnableLongPush[3]{0};

  Button btns[3]{leftBtnPin, centerBtnPin, rightBtnPin};

  bool isButtonPushedInternal(byte num);
  bool isButtonPushedLongInternal(byte num);
};