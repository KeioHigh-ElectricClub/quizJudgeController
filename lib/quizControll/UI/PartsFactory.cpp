#include "PartsFactory.h"

PartsFactory::PartsFactory(TFT_eSPI* display,
                           RecodeApplicationService* recodeApp, Config* config,
                           ButtonInput* button) {
  this->display = display;
  this->recodeApp = recodeApp;
  this->config = config;
  this->button = button;
}

std::unique_ptr<IParts> PartsFactory::createPage(PartsList page) {
  switch (page) {
    case PartsList::Header:
      return std::unique_ptr<IParts>(new Header(display, recodeApp, config));
      break;
    default:
      return nullptr;
  }
}