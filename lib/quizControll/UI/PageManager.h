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

  void init();
  void update();
  void draw();
  void changePage(PageList nextPage) override;

 private:
  std::unique_ptr<IPage> nowPage;
  std::unique_ptr<IPage> header;
  std::unique_ptr<IPage> footer;
  PageFactory* factory;
};
