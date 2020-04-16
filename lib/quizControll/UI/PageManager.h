#pragma once

#include <memory>

#include "IPage.h"
#include "IPageChange.h"
#include "PageFactory.h"
#include "PageList.h"

class PageManager : public IPageChange {
 public:
  PageManager(PageFactory* factory);
  ~PageManager() {}

  void update();
  void draw();
  void changePage(PageList nextPage) override;

 private:
  std::unique_ptr<IPage> nowPage;
  PageFactory* factory;
};
