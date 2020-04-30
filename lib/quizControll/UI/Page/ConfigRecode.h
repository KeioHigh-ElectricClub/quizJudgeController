#pragma once

#include "Application/Recode/RecodeApplicationService.h"
#include "ConfigPage.h"

class ConfigRecode : public ConfigPage {
 public:
  ConfigRecode(TFT_eSPI* display, IPageChange* changer, ButtonInput* button,
               RecodeApplicationService* recodeApp);
  ~ConfigRecode() {}

  void init() override;
  void update() override;
  void draw() override;
};