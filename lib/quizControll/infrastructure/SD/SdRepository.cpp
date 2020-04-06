#include "SdReposiroty.h"

SdRepository::SdRepository(byte cs, byte cd, byte wp) {
  this->cs = cs;
  if (cd != 0xff) this->cd = cd;
  if (wp != 0xff) this->wp = wp;

  pinMode(cd, INPUT_PULLUP);
  pinMode(wp, INPUT_PULLUP);
}

bool SdRepository::init() {
  if (!(isConnected() || canWrite())) return false;

  if (!SD.begin(cs, SPI, 24000000)) return false;
  int counter = 1;
  while (true) {
    if (!SD.exists(createFileName(counter))) break;
    counter++;
  }
  nowFileName = createFileName(counter);
  File newFile = SD.open(nowFileName, FILE_WRITE);
  newFile.println("問題番号,回答者番号,結果");
  newFile.close();
  SD.end();

  questionNum = 0;

  return true;
}

bool SdRepository::storeResetRecode() {
  char buffer[10];
  sprintf(buffer, "%d,Reset", questionNum);
  if (!write(buffer)) return false;
  questionNum++;
  return true;
}

bool SdRepository::store(std::unique_ptr<Result> result) {
  byte respondentNum = result->getRespondentNum();
  bool erratum = result->getErratum() == Erratum::CORRECT;

  char buffer[15];
  sprintf(buffer, "%d,%d,%d", questionNum, respondentNum, erratum);

  if (!write(buffer)) return false;
  if (erratum) questionNum++;

  return true;
}

bool SdRepository::write(String data) {
  if (!(isConnected() || canWrite())) return false;
  if (!SD.begin(cs, SPI, 24000000)) return false;
  File file = SD.open(nowFileName, FILE_APPEND);
  file.println(data);
  file.close();
  SD.end();
}

String SdRepository::createFileName(int num) {
  String fileName = "LOG";
  if (num < 100) fileName += "0";
  if (num < 10) fileName += "0";
  fileName += num;
  fileName += ".csv";
  return fileName;
}

bool SdRepository::isConnected() { return !digitalRead(cd); }

bool SdRepository::canWrite() { return !digitalRead(wp); }
