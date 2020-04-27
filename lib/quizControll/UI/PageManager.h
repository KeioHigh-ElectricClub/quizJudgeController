#pragma once

#include <memory>

#include "IPage.h"
#include "IPageChange.h"
#include "IParts.h"
#include "PageFactory.h"
#include "PageList.h"
#include "Parts/Footer.h"
#include "Parts/Header.h"
#include "PartsFactory.h"
#include "TFT_eSPI.h"

class PageManager : public IPageChange {
 public:
  PageManager(PageFactory* pageFactory, PartsFactory* partsFactory,
              TFT_eSPI* display);
  ~PageManager() {}

  void init();
  void update();
  void draw();
  void changePage(PageList nextPage) override;
  void setFooterMessage(String left, String center, String right);

 private:
  std::unique_ptr<IPage> nowPage;
  std::unique_ptr<IParts> header;
  PageFactory* pageFactory;
  PartsFactory* partsFactory;
  TFT_eSPI* display;
};
