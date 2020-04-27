#pragma once

#include <memory>

#include "Application/Config/Config.h"
#include "Application/Recode/RecodeApplicationService.h"
#include "IParts.h"
#include "TFT_eSPI.h"
#include "UI/PartsList.h"
#include "infrastructure/Button/ButtonInput.h"
// #include "UI/Page/MainPage.h"

#include "Parts/Header.h"

class PartsFactory {
 public:
  PartsFactory(TFT_eSPI* display, RecodeApplicationService* recodeApp,
               Config* config, ButtonInput* button);
  std::unique_ptr<IParts> createPage(PartsList parts);

 protected:
  TFT_eSPI* display;
  RecodeApplicationService* recodeApp;
  Config* config;
  ButtonInput* button;
};