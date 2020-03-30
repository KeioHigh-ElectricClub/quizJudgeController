#pragma once

class IConfigOutput {
  IConfigOutput() {}
  virtual ~IConfigOutput() {}

  virtual bool setLimit();
  virtual bool softReset();
};