// #include <Arduino.h>
#include <unity.h>

#include "Application/Recode/RecodeApplicationService.h"
#include "Test/TestRepository.h"
#include "domain/Recode/AnswerRight.h"
#include "domain/Recode/Result.h"

void testRespondent() {
  for (byte i = 0; i < 20; i++) {
    AnswerRight right(i);
    TEST_ASSERT_EQUAL(i, right.getRespondentNum());
  }
}

void testSetErratum() {
  AnswerRight right(1);
  right.setErratum(Erratum::CORRECT);
  TEST_ASSERT_EQUAL(Erratum::CORRECT, right.getErratum());
  right.setErratum(Erratum::INCORRECT);
  TEST_ASSERT_EQUAL(Erratum::INCORRECT, right.getErratum());
}

void testManager() {
  RecodeApplicationService manager;
  for (byte i = 0; i < 20; i++) {
    manager.createAnswerRight(i);
    TEST_ASSERT_EQUAL(i, manager.getRecode().getRespondentNum());
    manager.reset();
  }
}

void testManagerWithRepository() {
  TestRepository repository;
  RecodeApplicationService manager(&repository);
  for (byte i = 0; i < 20; i++) {
    manager.createAnswerRight(i);
    TEST_ASSERT_EQUAL(i, manager.getRecode().getRespondentNum());
    manager.showIncorrect();
    TEST_ASSERT_EQUAL(i, repository.getRespondent(i));
    TEST_ASSERT_EQUAL(false, repository.getIsCorrect(i));
  }
}

void testManagerWithoutAnswerRight() {
  RecodeApplicationService manager;

  TEST_ASSERT_EQUAL(false, manager.getRecode().getExistsRight());
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(testRespondent);
  RUN_TEST(testSetErratum);
  RUN_TEST(testManager);
  RUN_TEST(testManagerWithRepository);
  RUN_TEST(testManagerWithoutAnswerRight);
  UNITY_END();
}

void loop() {}