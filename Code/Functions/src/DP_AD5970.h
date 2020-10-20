#ifndef DP_AD5970_H
#define DP_AD5970_H

#include <SPI.h>
#include <Arduino.h>

class DP_AD5970{
  public:
  DP_AD5970(int ss);

  //method
void  DPOT_WR(int amp);

  //variables
  int _ss;
  
  private:
  const uint16_t DpotReg=0x0400; //data register of AD5270
};



#endif
