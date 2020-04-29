#pragma once

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "ConfigPage.h"

class ConfigLimit : public ConfigPage {
 public:
  ConfigLimit(TFT_eSPI* display, IPageChange* changer, ButtonInput* button,
              RecodeApplicationService* recodeApp, Config* config);
  ~ConfigLimit() {}

  void init() override;
  void update() override;
  void draw() override;

 private:
  Config* config;
};