#ifndef DP_AD5970_H
#define DP_AD5970_H

#include <SPI.h>
#include <Arduino.h>

class DP_AD5970{
  public:
  DP_AD5970(int ss);

  //method
void  DPOTinit(SPIClass * spi);
void  DPOT_WR(int amp, SPIClass * spi);

  //variables
  int _ss;
  
};



#endif
