#pragma once

#include <Arduino.h>

#include <vector>

#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Result.h"

class TestRepository : public IResultRepository {
 public:
  TestRepository() {}
  ~TestRepository() {}
  bool init() {
    Serial.println("repository init");
    storage.clear();
    return true;
  }

  bool store(RecodePtr result) override {
    Data received;
    received.respondent = result->getRespondentNum();
    received.isCorrect = result->getErratum() == Erratum::CORRECT;
    storage.push_back(received);
    return true;
  }
  bool storeResetRecode() {
    Serial.println("Reset");
    return true;
  }

  int getRespondent(int num) { return storage[num].respondent; }
  bool getIsCorrect(int num) { return storage[num].isCorrect; }

 private:
  struct Data {
    int respondent;
    bool isCorrect;
  };

  std::vector<Data> storage;
};