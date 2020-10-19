#ifndef FG_AD5932_H
#define FG_AD5932_H

#include <SPI.h>
#include <Arduino.h>


class FG_AD5932{
  public:
  FG_AD5932(int ss, int ctrl, int stb);
  
  //Methods
  void FGinit();
  void FG_WR(float freq);
  void FG_ON();

  int _ss;
  int _ctrl;
  int _stb;
  
  private:
  uint16_t FLSB(uint32_t w);
  uint16_t FMSB(uint32_t w);
  const uint16_t FsLSBReg=0xC000;//frequency start register of AD5932 LSB
  const uint16_t FsMSBReg=0xD000;//frequency start register of AD5932 MSB
};


#endif
