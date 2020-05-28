#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include <memory>

#include "domain/Recode/IResultRepository.h"
#include "domain/Recode/Result.h"

constexpr uint32_t SD_SPEED = 24000000;

class SdRepository : public IResultRepository {
 public:
  SdRepository(byte cs, byte cd = 0xff, byte wp = 0xff);
  ~SdRepository();

  bool store(std::unique_ptr<Result> result);
  bool storeResetRecode();
  bool init();

 private:
  byte cs = 0, cd = 0xff, wp = 0xff;
  String nowFileName;
  int questionNum = 0;

  String createFileName(int num);
  bool write(String data);
  bool isConnected();
  bool canWrite();
};