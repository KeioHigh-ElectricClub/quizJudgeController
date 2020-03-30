#ifndef UNIT_TEST

#include <Arduino.h>

#include <DFRobotDFPlayerMini.h>
#include <SD.h>
#include "TFT_eSPI.h"
#include "domain/AnswerRight.h"

void setup() {
  Serial.begin(115200);
  AnswerRight right(1);
  right.setErratum(Erratum::CORRECT);
  // TEST_ASSERT_EQUAL(Erratum::CORRECT, right.getErratum());
  right.setErratum(Erratum::INCORRECT);
  // TEST_ASSERT_EQUAL(Erratum::INCORRECT, right.getErratum());
}
void loop() {}

#endif