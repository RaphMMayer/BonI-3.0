#include "DP_AD5970.h"

SPISettings DPOTsetting(8000000, MSBFIRST, SPI_MODE1);

DP_AD5970::DP_AD5970(int ss){
  pinMode(ss, OUTPUT); //DP_ss
  _ss=ss;
}

void DP_AD5970::DPOT_WR(int amp, SPIClass * spi){
  // take the SS pin low to select the chip:
  spi->beginTransaction(DPOTsetting);
  digitalWrite(_ss, LOW);
  delay(10);
  
  //  send in the address and value via SPI:
  spi->transfer16(0x0400+amp/2); //calculation desired amplitude/2 in mV
  Serial.print(0x0400+amp/2);
  delay(10);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(_ss, HIGH);
  spi->endTransaction();
}
void DP_AD5970::DPOTinit(SPIClass * spi){
  spi->beginTransaction(DPOTsetting);
  digitalWrite(_ss, LOW);
  delay(10);
  //  send in the address and value via SPI:
  spi->transfer16(0x1C03);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(_ss, HIGH);
  spi->endTransaction();
}
