#pragma once

#include "domain/Config/Limit.h"

class IConfigOutput {
 public:
  virtual ~IConfigOutput(){};

  virtual bool setLimit(Limit limit) = 0;
};