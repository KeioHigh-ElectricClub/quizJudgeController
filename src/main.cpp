#ifndef UNIT_TEST

#include <Arduino.h>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "TFT_eSPI.h"
#include "Test/TestJudgeOutput.h"
#include "Test/TestRepository.h"
#include "UI/PageFactory.h"
#include "UI/PageManager.h"
#include "UI/PartsFactory.h"
#include "infrastructure/Button/ButtonInput.h"

TFT_eSPI display(320, 240);

TestRepository repository;
TestJudgeOutput judgeOutput;
RecodeApplicationService recodeService(judgeOutput, repository);
Config config(judgeOutput);
ButtonInput button;
PageFactory pageFactory(&display, &recodeService, &config, &button);
PartsFactory partsFactory(&display, &recodeService, &config, &button);
PageManager manager(pageFactory, partsFactory, &display);

void setup() {
  Serial.begin(115200);

  PageList pageArray[] = {PageList::Menu, PageList::ConfigLimit};

  button.init();

  try {
    manager.init();
    manager.update();
    manager.draw();
    for (byte i = 0; i < 2; i++) {
      manager.update();
      manager.changePage(pageArray[i]);
      manager.draw();
    }
  } catch (const char* e) {
    Serial.println("exception");
    Serial.println(e);
  }
}
void loop() {}

#endif