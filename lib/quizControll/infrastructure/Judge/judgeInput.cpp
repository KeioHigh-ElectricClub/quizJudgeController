#include "judgeInput.h"

JudgeInput::JudgeInput(byte sda, byte scl, RecodeApplicationService& recodeApp)
    : recodeApp(recodeApp) {
  Wire.begin(sda, scl);
}
void JudgeInput::begin() {
  send(0x1A);
  delay(50);
  send(0x46);
}
void JudgeInput::update() {
  byte data = receive(0x52);
  if (data & 0x00000001) {
  }
  if (!(data & 0x00000010)) return;
  byte respondent = receive(0xAA);
  byte waiting = (data & 0x11111100) >> 2;
  recodeApp.createAnswerRight(respondent, waiting);
}

bool JudgeInput::send(byte select) {
  Wire.beginTransmission(0x64);
  Wire.write(select);
  return !Wire.endTransmission();
}
byte JudgeInput::receive(byte select) {
  send(select);
  Wire.requestFrom(0x64, 1);
  while (!Wire.available()) {
  }
  return Wire.read();
}