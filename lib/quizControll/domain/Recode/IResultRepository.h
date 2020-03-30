#pragma once

#include <memory>
#include "Result.h"

class IResultRepository {
 public:
  IResultRepository() {}
  virtual ~IResultRepository() {}

  virtual bool store(std::unique_ptr<Recode> result);
};