#pragma once

#include <JC_Button.h>

#include <memory>

class ButtonInput {
 public:
  ButtonInput();
  ~ButtonInput() {}

  void init();
  void update();

  void setEnableLongPush(bool left, bool center, bool right);
  bool isLeftPushed();
  bool isLeftPushedLong();
  bool isCenterPushed();
  bool isRightPushed();

 private:
  static const uint8_t buttonPin[];

  bool isButtonLongPushed[3] = {0};
  bool prevPagePushedButton[3] = {0};
  bool prevPushedButtonLong[3] = {0};
  bool isButtonPushed[3] = {0};
  bool isEnableLongPush[3] = {0};

  std::unique_ptr<Button> btns[3];
  bool aaa = false;

  bool isButtonPushedInternal(byte num);
  bool isButtonPushedLongInternal(byte num);
};