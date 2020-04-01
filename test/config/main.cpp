#include <Arduino.h>
#include <unity.h>

#include "Application/Config/Config.h"
#include "Test/TestJudgeOutput.h"

TestJudgeOutput judgeOutput;

void testConfig() {
  Config config(&judgeOutput);
  config.setLimit(Limit::UNTIL1);
  config.setLimit(Limit::UNTIL2);
  config.setLimit(Limit::UNTIL20);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(testConfig);
  UNITY_END();
}

void loop() {}