#pragma once

#include "AudioOutput.h"

// #define SRC_FS 44100           // Source Sampling Rate [Hz]
#define OSR 4  // Over Sampling Rate (1~8)
// #define DAC_FS (OSR * SRC_FS)  // DAC Sampling Rate [Hz]
#define SPF 882   // Sample per Frame (Buffer処理単位)
#define DSOMAX 4  // Max. of DeltaSigma Order

class AudioOutputDeltaSigmaDAC : public AudioOutput {
 public:
  AudioOutputDeltaSigmaDAC();
  virtual ~AudioOutputDeltaSigmaDAC() override;
  virtual bool SetRate(int hz) override;
  virtual bool SetBitsPerSample(int bits) override;
  virtual bool SetChannels(int channels) override;
  virtual bool begin() override;
  virtual bool ConsumeSample(int16_t sample[2]) override;
  virtual bool stop() override;
  static bool isI2sOn;

 protected:
  void filterProcess(int32_t l, int32_t r);

  //   char src_buf[4 * SPF] = {0};  // 16bit/spl*stereo*spl/Frame
  //   char dac_buf[4 * SPF * OSR] = {
  //       0};  // 16bit/spl*stereo*spl/Frame *OverSamplRate

  // DAC Lvl.用 Gain/Offset定義
  // struct {
  //   const float gain, offset;
  // } fc[3] = {
  //     // MenuMode Gain 8bit切上補正 純オフセット
  //     {+1.000000000, +128.00000},    // Thru     1/1  +128
  //     {+0.333333333, +21973.33333},  // Mid 1/3  1/3  +128 (1-1/3)*(2^15)
  //     {+0.333333333, +213.33333},    // Low 1/3  1/3  +128       +256/3
  // };
  const float gain = +0.333333333;
  const float offset = +213.33333;

  struct {  ////// Biquad Filter Coef.
    const float k, a1, a2, b1,
        b2;  // b0 is fixed to '1', b1 & b2 MUST BE normalized
  } lpf = {
//// OSR Val.
#if OSR >= 8  // fc = 0.05fs
    .k = +0.0208307252,
    .a1 = -1.552247273,
    .a2 = +0.635570174,
#elif OSR >= 6  // fc = 0.067fs
    .k = +0.0347860374,
    .a1 = -1.407505344,
    .a2 = +0.546649494,
#elif OSR >= 4  // fc = 0.1fs
    .k = +0.0697808942,
    .a1 = -1.126428906,
    .a2 = +0.405552483,
#elif OSR >= 2  // fc = 0.2fs
    .k = +0.2132071969,
    .a1 = -0.339151185,
    .a2 = +0.191979973,
#else  // OSR < 2              // fc = 0.4fs (18kHz at 44k1, 20k at 48k)
    .k = +0.6632098902,
    .a1 = +1.209579277,
    .a2 = +0.443260284,
#endif
    .b1 = +2,
    .b2 = +1,  // Fixed (b0,b1,b2)=(+1,+2,+1)
  };
};