#pragma once

#include <Arduino.h>

class RecodeModel {
 public:
  RecodeModel() { existsRight = false; }
  RecodeModel(byte respondentNum) { this->respondentNum = respondentNum; }

  bool getExistsRight() { return existsRight; }
  byte getRespondentNum() { return respondentNum; }

 private:
  bool existsRight = true;
  byte respondentNum = 0xff;
};
