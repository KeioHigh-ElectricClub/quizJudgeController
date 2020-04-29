#pragma once

#include "IConfigOutput.h"
#include "domain/Config/Limit.h"

class Config {
 public:
  Config(IConfigOutput& output);
  bool setLimit(Limit limit);
  Limit getLimit();

 private:
  IConfigOutput& output;
  Limit nowLimit;
};