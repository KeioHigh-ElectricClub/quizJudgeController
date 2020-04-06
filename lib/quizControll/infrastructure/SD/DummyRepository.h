#pragma once

#include <memory>

#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Result.h"

class DummyRepository : public IResultRepository {
 public:
  DummyRepository() {}
  ~DummyRepository() {}

  bool store(std::unique_ptr<Result> result) {}
  bool init() {}
};