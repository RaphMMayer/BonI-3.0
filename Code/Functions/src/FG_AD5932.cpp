#include "FG_AD5932.h"

SPISettings FGsetting(8000000, MSBFIRST, SPI_MODE2);

FG_AD5932::FG_AD5932(int ss, int ctrl, int stb){
  pinMode(ss, OUTPUT); //FG_ss
  pinMode(ctrl, OUTPUT); //FG_ctrl
  pinMode(stb, OUTPUT); //FG_standby
  _ss=ss;
  _ctrl=ctrl;
  _stb=stb;
}

void FG_AD5932::FGinit(SPIClass * spi){
  spi->beginTransaction(FGsetting);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0xED3); //Initialize setting
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(_ss, HIGH);
  delay(10);

  spi->endTransaction();
  }


void FG_AD5932::FG_WR(int freq,SPIClass * spi){
  spi->beginTransaction(FGsetting);
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(10);
  digitalWrite(_ss, HIGH);
  delay(10);
  digitalWrite(_ss, LOW);
  delay(10);
  spi->transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(10);
  digitalWrite(_ss, HIGH);
  spi->endTransaction();
}

void FG_AD5932::FG_ON(SPIClass * spi){
  Serial.print(_ctrl);
  digitalWrite(_ctrl, HIGH); //A low to high transition makes the FG update its frequency output
  delay(10);
  digitalWrite(_ctrl, LOW);
}

void FG_AD5932::FG_STB(int s,SPIClass * spi){
  Serial.print(_stb);
  if (s==1){
  digitalWrite(_stb, HIGH);//pulled high to disable the FG
  }
  else{
  digitalWrite(_stb, LOW);//pulled low to enable the FG(the pin is pulled down by default)
  }
}

uint16_t FG_AD5932::FLSB(int w){
  return (uint16_t)((w) & 0xFFF); //get the LEAST significant bits of the 32 bits word and convert it to 16 bits
}

uint16_t FG_AD5932::FMSB(int w){
  return (uint16_t) ((w) >>12);  //get the MOST significant bits of the 32 bits word and convert it to 16 bits
}
