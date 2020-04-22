#pragma once

#include <Arduino.h>

class RecodeModel {
 public:
  RecodeModel() { existsRight = false; }
  RecodeModel(byte respondentNum, byte waiting) {
    this->respondentNum = respondentNum;
    this->waiting = waiting;
  }

  bool getExistsRight() { return existsRight; }
  byte getRespondentNum() { return respondentNum; }
  byte getWainting() { return waiting; }

 private:
  bool existsRight = true;
  byte respondentNum = 0xff;
  byte waiting = 0;
};
