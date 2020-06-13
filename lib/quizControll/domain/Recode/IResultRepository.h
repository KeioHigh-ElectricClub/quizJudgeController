#pragma once

#include <memory>

#include "Result.h"

using RecodePtr = std::unique_ptr<Recode>;

class IResultRepository {
 public:
  virtual ~IResultRepository() {}

  virtual bool store(RecodePtr result) = 0;
  virtual bool storeResetRecode() = 0;
  virtual bool init() = 0;
};