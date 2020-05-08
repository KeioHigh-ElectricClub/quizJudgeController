#pragma once

#include "UI/PageList.h"

class IPageChange {
 public:
  virtual void changePage(PageList nextPage) = 0;
};