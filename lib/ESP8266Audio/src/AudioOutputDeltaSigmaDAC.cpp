#include "AudioOutputDeltaSigmaDAC.h"
bool AudioOutputDeltaSigmaDAC::isI2sOn;

#include "driver/i2s.h"

AudioOutputDeltaSigmaDAC::AudioOutputDeltaSigmaDAC() {
  if (!isI2sOn) {
    i2s_config_t i2s_config = {
        .mode =
            (i2s_mode_t)(I2S_MODE_DAC_BUILT_IN | I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100 * OSR,
        .bits_per_sample =
            I2S_BITS_PER_SAMPLE_16BIT,  // 内部DACは上位8bitが再生対象
        .channel_format =
            I2S_CHANNEL_FMT_RIGHT_LEFT,  // ステレオ。左右データ書込必要
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 16,  // 現物合わせ
        .dma_buf_len = 256,   // 1024以下。
        .use_apll = false  // 75kHz以上(OSR>=2)でtrue指定すると正常動作しない
    };
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, NULL);
  }
  isI2sOn = true;
  SetGain(1.0);
  SetRate(44100 * OSR);

  int16_t samples[2] = {0x0, 0x0};

  // while (!ConsumeSample(samples)) {
  // }
}
AudioOutputDeltaSigmaDAC::~AudioOutputDeltaSigmaDAC() {
  if (isI2sOn) {
    audioLogger->printf("UNINSTALL I2S\n");
    i2s_driver_uninstall(I2S_NUM_0);  // stop & destroy i2s driver
  }
}
bool AudioOutputDeltaSigmaDAC::SetRate(int hz) {
  this->hertz = hz;
  i2s_set_sample_rates(I2S_NUM_0, hz * OSR);
  return true;
}
bool AudioOutputDeltaSigmaDAC::SetBitsPerSample(int bits) {
  if ((bits != 16) && (bits != 8)) return false;
  this->bps = bits;
  return true;
}
bool AudioOutputDeltaSigmaDAC::SetChannels(int channels) { return false; }
bool AudioOutputDeltaSigmaDAC::begin() {
  // uint32_t d = 11136;
  // d |= d << 16;
  // i2s_write_bytes(I2S_NUM_0, (char*)(&d), 4, portMAX_DELAY);
  return true;
}
bool AudioOutputDeltaSigmaDAC::ConsumeSample(int16_t sample[2]) {
  static float z[3] = {32768.0};        // Biquad IIR LPF z work
  static int32_t iqtout = 0;            // int Quantizer Output
  static int32_t isigma[DSOMAX] = {0};  // int Sigma[Order] Data;
  char dac_buf[4 * OSR];
  uint32_t* pto32 = (uint32_t*)dac_buf;
  int16_t ms[2];

  ms[0] = sample[0];
  ms[1] = sample[1];
  MakeSampleStereo16(ms);

  uint16_t l, r;
  uint32_t result;

  l = (uint16_t)Amplify(ms[0]) ^ 0x8000;
  r = (uint16_t)Amplify(ms[1]) ^ 0x8000;
  result = (l + r) >> 1;
  float fd = (float)result, fin;

  fd = fd * gain + offset;

  for (int j = 0; j < OSR; j++) {  ////// xOSR Over Sampling Loop
    z[2] = z[1];                   // Biquad z2 Shift
    z[1] = z[0];                   // Biquad z1 Shift
    z[0] = lpf.k * fd - lpf.a1 * z[1] - lpf.a2 * z[2];  // Biquad z0 Update
    fin = z[0] + lpf.b1 * z[1] + lpf.b2 * z[2];         // Biquad result

    int32_t iin = (int32_t)(fin + 0.5);  // float -> i32 data
    for (int k = 0; k < 3; k++) {        //// xOrder DeltaSigma Loop(dso=0:Thru)
      isigma[k] += (iin - iqtout);       // Delta-Sigma Core
      iin = isigma[k];                   // Update Output (iin)
    }                                    //// Delta-Sigma Loop End
    iqtout = iin & 0xffffff00;  // Quantize(8bDACで無視される下位8bitをMask)

    result = (uint32_t)constrain(iqtout, 0, 65535);  // Clip to u16 size
    // Serial.println(result);
    result |= (result << 16);  // u16 Mono → Dual u16 Mono
    *(pto32++) = result;       // DAC出力バッファに書込
  }                            ////// OverSampling Loop End
  return i2s_write_bytes(I2S_NUM_0, dac_buf, sizeof(dac_buf), 0);
}

bool AudioOutputDeltaSigmaDAC::stop() {
  int buffersize = 256 * 16;
  int16_t samples[2] = {0x0, 0x0};

  while (!ConsumeSample(samples)) {
  }
  // i2s_zero_dma_buffer(I2S_NUM_0);
  return true;
}