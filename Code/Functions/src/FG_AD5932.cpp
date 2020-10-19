#include "FG_AD5932.h"

SPISettings FGsetting(8000000, MSBFIRST, SPI_MODE2);
SPISettings DPOTsetting(8000000, MSBFIRST, SPI_MODE1);

FG_AD5932::FG_AD5932(int ss, int ctrl, int stb){
  pinMode(ss, OUTPUT); //FG_ss
  pinMode(ctrl, OUTPUT); //FG_ctrl
  pinMode(stb, OUTPUT); //FG_standby
  _ss=ss;
  _ctrl=ctrl;
  _stb=stb;
}

void FG_AD5932::FGinit(){
  SPI.beginTransaction(FGsetting);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0xED3); //Initialize setting
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0x63E8);//Period of increment=1000
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(_ss, HIGH);
  delay(10);
  
  digitalWrite(_ss, LOW);
  delay(10);
  SPI.transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(_ss, HIGH);
  delay(10);
  }


void FG_AD5932::FG_WR(float freq){
  SPI.beginTransaction(FGsetting);
  digitalWrite(_ss, LOW);
  delay(100);
  SPI.transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(100);
  digitalWrite(_ss, HIGH);
  delay(100);
  digitalWrite(_ss, LOW);
  delay(100);
  SPI.transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(100);
  digitalWrite(_ss, HIGH);
  SPI.endTransaction();
}

void FG_AD5932::FG_ON(){
  SPI.beginTransaction(FGsetting);
  Serial.print(_ctrl);
  digitalWrite(_ctrl, HIGH);
  delay(100);
  digitalWrite(_ctrl, LOW);
  SPI.endTransaction();
}

uint16_t FG_AD5932::FLSB(uint32_t w){
  return (uint16_t)((w) & 0xFFF);
}

uint16_t FG_AD5932::FMSB(uint32_t w){
  return (uint16_t) ((w) >>12);
}
