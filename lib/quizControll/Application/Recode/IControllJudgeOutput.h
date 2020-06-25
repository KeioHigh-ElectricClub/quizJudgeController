#pragma once

class IControllJudgeOutput {
 public:
  virtual ~IControllJudgeOutput(){};

  virtual bool softReset() = 0;
  virtual bool assignRight() = 0;
};