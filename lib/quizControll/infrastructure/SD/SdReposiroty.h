#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include <memory>

#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Recode.h"

class SdRepository : public IResultRepository {
 public:
  SdRepository();
  ~SdRepository();

  bool store(std::unique_ptr<Recode> result);
  bool init();
};