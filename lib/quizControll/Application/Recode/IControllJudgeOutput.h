#pragma once

class IControllJudgeOutput {
 public:
  IControllJudgeOutput() {}
  virtual ~IControllJudgeOutput() {}

  virtual bool softReset();
  virtual bool assignRight();
};