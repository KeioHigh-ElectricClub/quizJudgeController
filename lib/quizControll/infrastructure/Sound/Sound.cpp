#include "Sound.h"

QueueHandle_t queueHandle;

AudioGeneratorMP3* mp3;
AudioOutputDeltaSigmaDAC* i2s;
#include "driver/i2s.h"

AudioFileSourcePROGMEM* sound;

struct AudioFile {
  char* data;
  size_t size;
};

void task0(void* d) {
  String fileNames[] = {"/correct.mp3", "/incorrect.mp3", "/push.mp3"};
  AudioFile files[3];

  for (byte i = 0; i < 3; i++) {
    auto file = SPIFFS.open(fileNames[i]);
    files[i].data = new char[file.size()];
    file.readBytes(files[i].data, file.size());
    files[i].size = file.size();
    file.close();
  }

  i2s = new AudioOutputDeltaSigmaDAC;
  mp3 = new AudioGeneratorMP3();

  Serial.println("music start");

  while (true) {
    Sound next;
    auto status = xQueueReceive(queueHandle, &next, 0);
    if (status == pdPASS) {
      if (mp3->isRunning()) mp3->stop();
      delete sound;
      AudioFile* file = &files[static_cast<int>(next)];
      sound = new AudioFileSourcePROGMEM(file->data, file->size);
      mp3->begin(sound, i2s);
      Serial.printf("play %d\n", static_cast<int>(next));
    }
    if (mp3->isRunning()) {
      if (!mp3->loop()) {
        // i2s_zero_dma_buffer(I2S_NUM_0);
        mp3->stop();
      }
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