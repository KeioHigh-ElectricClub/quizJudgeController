#pragma once

#include <Arduino.h>
#include <SPIFFS.h>
//
#include <AudioFileSourceSPIFFS.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <FreeRTOS.h>

extern QueueHandle_t queueHandle;

enum class Sound { CORRECT, INCORRECT, PUSH };

void soundSetup();
void soundPlay(Sound type);