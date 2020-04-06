#pragma once

#include "IConfigOutput.h"
#include "domain/Config/Limit.h"

class Config {
 public:
  Config(IConfigOutput* output) { this->output = output; }
  bool setLimit(Limit limit);

 private:
  IConfigOutput* output;
  Limit nowLimit;
};