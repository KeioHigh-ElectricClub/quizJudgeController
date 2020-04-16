#pragma once

class IPageChange {
 public:
  virtual void changePage(PageList nextPage) = 0;
};