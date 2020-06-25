#include "judgeInput.h"

JudgeInput::JudgeInput(byte sda, byte scl, RecodeApplicationService& recodeApp)
    : recodeApp(recodeApp) {
  Wire.begin(sda, scl);
}
void JudgeInput::begin() {
  send(0x1A);
  delay(1200);
  send(0x46);
  Serial.println("i2c init");
}
void JudgeInput::update() {
  byte data = receive(0x52);
  // Serial.printf("judge status->%x\n", data);
  if (data & 0b00000001) {
    soundPlay(Sound::PUSH);
  }
  if (data & 0b00000010) {
    byte respondent = receive(0x54);
    Serial.printf("respondent->%d\n", respondent);
    recodeApp.createAnswerRight(respondent);
  }
  if (data & 0b0100) {
    byte waiting = receive(0x56);
    recodeApp.setWaiting(waiting);
    Serial.printf("waiting->%d\n", waiting);
  }
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