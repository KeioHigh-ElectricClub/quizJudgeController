#include "judgeOutput.h"

JudgeOutput::JudgeOutput(byte sda, byte scl) { Wire.begin(sda, scl); }

bool JudgeOutput::softReset() { return send(0xAC); }

bool JudgeOutput::assignRight() { return send(0xAE); }
bool JudgeOutput::setLimit(Limit limit) {
  byte data;
  switch (limit) {
    case Limit::UNTIL1:
      data = 1;
      break;
    case Limit::UNTIL2:
      data = 2;
      break;
    case Limit::UNTIL20:
      data = 20;
      break;
    default:
      data = 1;
  }
  return send(0x50, data);
}

bool JudgeOutput::send(byte select) {
  Wire.beginTransmission(0x64);
  Wire.write(select);
  return !Wire.endTransmission();
}
bool JudgeOutput::send(byte select, byte data) {
  Wire.beginTransmission(0x64);
  Wire.write(select);
  Wire.write(data);
  return !Wire.endTransmission();
}