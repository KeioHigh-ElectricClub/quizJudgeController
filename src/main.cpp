#ifndef UNIT_TEST

#include <Arduino.h>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "TFT_eSPI.h"
#include "Test/TestJudgeOutput.h"
#include "Test/TestRepository.h"
#include "UI/PageFactory.h"
#include "UI/PageManager.h"

TFT_eSPI display(320, 240);

TestRepository repository;
TestJudgeOutput judgeOutput;
RecodeApplicationService recodeService(&judgeOutput, &repository);
Config config(&judgeOutput);
PageFactory factory(&display, &recodeService, &config);
PageManager manager(&factory);

void setup() {
  Serial.begin(115200);

  try {
    manager.init();
    manager.update();
    manager.draw();
  } catch (const char* e) {
    Serial.println("exception");
    Serial.println(e);
  }
}
void loop() {}

#endif