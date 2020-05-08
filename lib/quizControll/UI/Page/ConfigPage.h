#pragma once
#include <Arduino.h>

#include <functional>
#include <vector>

#include "Application/Recode/RecodeApplicationService.h"
#include "UI/IPage.h"

class ConfigPage : public IPage {
 public:
  ConfigPage(TFT_eSPI* display, IPageChange* changer, ButtonInput* button,
             RecodeApplicationService* recodeApp);
  virtual ~ConfigPage(){};
  virtual void init();
  virtual void update();
  virtual void draw();

 protected:
  struct Item {
    String name;
    std::function<void(void)> func;
  };
  std::vector<Item> items;

  byte positionIndex = 0;

  int rowXpos[2] = {41, 175};
  int colomnYpos[2] = {82, 142};
  const int itemWidth = 104;
  const int itemHeight = 82;

  void drawTitle(String title);

  RecodeApplicationService* recodeApp;
};