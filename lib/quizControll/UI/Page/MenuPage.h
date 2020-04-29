#pragma once

#include <functional>

#include "UI/IPage.h"
#include "UI/Parts/Footer.h"
#include "infrastructure/Button/ButtonInput.h"

constexpr byte MAX_PAGE = 2;

class MenuPage : public IPage {
 public:
  MenuPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button);
  ~MenuPage() {}

  void init() override;
  void update() override;
  void draw() override;

 private:
  struct Item {
    String name;
    std::function<void(void)> func;
  };

  Item items[MAX_PAGE][2];
  const char* ignoreItem = "IGNORE";

  byte pageIndex = 0;
  int positionIndex = 0;

  uint32_t frameColor(int pageIndex);

  void onLeftPushed();
  void onCenterPushed();
  void onRightPushed();
};