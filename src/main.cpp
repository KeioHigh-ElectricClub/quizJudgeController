#ifndef UNIT_TEST
#include <Arduino.h>
#include <SPIFFS.h>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "TFT_eSPI.h"
#include "Test/TestJudgeOutput.h"
#include "Test/TestRepository.h"
#include "UI/PageFactory.h"
#include "UI/PageManager.h"
#include "UI/PartsFactory.h"
#include "infrastructure/Button/ButtonInput.h"
#include "infrastructure/Sound/Sound.h"

TFT_eSPI display(240, 320);

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

  Serial.println("start");

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield();  // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nSPIFFS available!");

  // ESP32 will crash if any of the fonts are missing
  if (SPIFFS.exists("/YuGothic20.vlw") == false) Serial.println("no font");
  if (SPIFFS.exists("/YuGothic12.vlw") == false) Serial.println("no font");
  if (SPIFFS.exists("/YuGothic80.vlw") == false) Serial.println("no font");

  soundSetup();

  display.begin();
  display.setRotation(1);

  button.init();
  manager.init();

  Serial.println("end");
}
void loop() {
  try {
    manager.update();
    manager.draw();
  } catch (const char* e) {
    Serial.println("exception");
    Serial.println(e);
  }
  delay(50);
}

#endif