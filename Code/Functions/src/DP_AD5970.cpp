#include "DP_AD5970.h"

SPISettings DPOTsetting(8000000, MSBFIRST, SPI_MODE1);

DP_AD5970::DP_AD5970(int ss){
  pinMode(ss, OUTPUT); //DP_ss
  _ss=ss;
}

void DP_AD5970::DPOT_WR(int amp){
  // take the SS pin low to select the chip:
  SPI.beginTransaction(DPOTsetting);
  digitalWrite(_ss, LOW);
  delay(100);
  
  //  send in the address and value via SPI:
  SPI.transfer16(DpotReg+(uint16_t)(amp/2)); //calculation desired amplitude/2 in mV
  Serial.print(DpotReg+(uint16_t)(amp/2));
  delay(100);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(_ss, HIGH);
  SPI.endTransaction();
}
