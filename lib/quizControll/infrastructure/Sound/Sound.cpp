#include "Sound.h"

QueueHandle_t queueHandle;

AudioGeneratorMP3* mp3;
AudioOutputI2S* i2s;

AudioFileSourceSPIFFS* soundFiles[3];

void task0(void* d) {
  soundFiles[static_cast<int>(Sound::CORRECT)] =
      new AudioFileSourceSPIFFS("/correct.mp3");
  soundFiles[static_cast<int>(Sound::INCORRECT)] =
      new AudioFileSourceSPIFFS("/incorrect.mp3");
  soundFiles[static_cast<int>(Sound::PUSH)] =
      new AudioFileSourceSPIFFS("/push.mp3");
  i2s = new AudioOutputI2S(0, 2);
  mp3 = new AudioGeneratorMP3();

  Serial.println("music start");

  while (true) {
    Sound next;
    auto status = xQueueReceive(queueHandle, &next, 0);
    if (status == pdPASS) {
      if (mp3->isRunning()) mp3->stop();
      mp3->begin(soundFiles[static_cast<int>(next)], i2s);
      Serial.printf("play %d\n", static_cast<int>(next));
    }
    if (mp3->isRunning()) {
      if (!mp3->loop()) mp3->stop();
    }
    vTaskDelay(1);
  }
}

void soundSetup() {
  queueHandle = xQueueCreate(1, sizeof(Sound));

  xTaskCreatePinnedToCore(task0, "Sound", 4096, NULL, 1, NULL, 0);
}

void soundPlay(Sound type) {
  if (xQueueSend(queueHandle, &type, 1) != pdPASS) {
    Serial.println("failed to request play");
  };
}