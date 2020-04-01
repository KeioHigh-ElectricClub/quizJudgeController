#pragma once

#include "domain/Config/Limit.h"

class IConfigOutput {
 public:
  IConfigOutput() {}
  virtual ~IConfigOutput() {}

  virtual bool setLimit(Limit limit);
  virtual bool softReset();
};