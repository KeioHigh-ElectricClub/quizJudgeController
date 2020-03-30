#pragma once

#include "IConfigOutput.h"
#include "domain/Config/Limit.h"

class Config {
  Config(IConfigOutput* io) { this->io = io; }
  bool setLimit(Limit limit);
  bool softReset();

 private:
  IConfigOutput* io;
  Limit nowLimit;
};