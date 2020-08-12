#pragma once

#include <Arduino.h>
#include <FreeRTOS.h>
#include <SPIFFS.h>
//
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputDeltaSigmaDAC.h>

extern QueueHandle_t queueHandle;

enum class Sound { CORRECT, INCORRECT, PUSH };

void soundSetup();
void soundPlay(Sound type);