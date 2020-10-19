#include <SPI.h>

#define VSPI_MISO   MISO
#define VSPI_MOSI   23
#define VSPI_SCLK   18

#define FG1_SS     19
#define FG1_CTRL   21
#define FG1_STDB   5

#define DPOT1_SS   16

#define AMP1_EN    17

#define FG2_SS     2
#define FG2_CTRL   4
#define FG2_STDB   15

#define DPOT2_SS   12
#define AMP2_EN    13


#define FG3_SS     27
#define FG3_CTRL   14
#define FG3_STDB   26

#define DPOT3_SS   33

#define AMP3_EN    25

#define FLSB(w) ((uint16_t) ((w) & 0xFFF))
#define FMSB(w) ((uint16_t) ((w) >>12))

const uint16_t FsLSBReg=0xC000;//frequency start register of AD5932 LSB
const uint16_t FsMSBReg=0xD000;//frequency start register of AD5932 MSB
const uint16_t DpotReg=0x0400;//data register of AD5270

const float c4=261;
const float d4=293;
const float e4=329;
const float g4=415;
const float a5=0x94;



//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;

void setup() {
  Serial.begin(115200);
  //initialise instance of the SPIClass attached to VSPI
  vspi = new SPIClass(VSPI);
  vspi->begin();
  
  pinMode(FG1_SS, OUTPUT); //FG1_ss
  pinMode(FG1_CTRL, OUTPUT); //FG1_ctrl
  pinMode(FG1_STDB, OUTPUT); //FG1_standby
  pinMode(DPOT1_SS, OUTPUT); //DPOT1_ss
  pinMode(AMP1_EN, OUTPUT); //AMP1_enable
  
  pinMode(FG2_SS, OUTPUT); //FG2_ss
  pinMode(FG2_CTRL, OUTPUT); //FG2_ctrl
  pinMode(FG2_STDB, OUTPUT); //FG2_standby
  pinMode(DPOT2_SS, OUTPUT); //DPOT2_ss
  pinMode(AMP2_EN, OUTPUT); //AMP2_enable
  
  pinMode(FG3_SS, OUTPUT); //FG3_ss
  pinMode(FG3_CTRL, OUTPUT); //FG3_ctrl
  pinMode(FG3_STDB, OUTPUT); //FG3_standby
  pinMode(DPOT3_SS, OUTPUT); //DPOT3_ss
  pinMode(AMP3_EN, OUTPUT); //AMP3_enable

  FGinit();
}

SPISettings FGsetting(8000000, MSBFIRST, SPI_MODE2);
SPISettings DPOTsetting(8000000, MSBFIRST, SPI_MODE1);


void loop() {
  DPOT1_WR(1000);
  FG1_WR(c4);
  FG1_ON();
  delay(1000);
  FG1_WR(e4);
  FG1_ON();
  delay(1000);
  FG1_WR(g4);
  FG1_ON();
  delay(1000);
  
}

void FGinit(){
  vspi->beginTransaction(FGsetting);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG1_SS, HIGH);
  delay(10);
  
  digitalWrite(FG1_SS, LOW);
  delay(10);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG1_SS, HIGH);
  delay(10);

  //FG2
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG2_SS, HIGH);
  delay(10);
  
  digitalWrite(FG2_SS, LOW);
  delay(10);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG2_SS, HIGH);
  delay(10);

//FG3
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  digitalWrite(FG3_SS, LOW);
  delay(10);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG3_SS, HIGH);
  delay(10);
  
  vspi->endTransaction();
}


void DPOT1_WR(int ampl){
  // take the SS pin low to select the chip:
  vspi->beginTransaction(DPOTsetting);
  digitalWrite(DPOT1_SS, LOW);
  delay(100);
  //  send in the address and value via SPI:
  SPI.transfer16(DpotReg+(uint16_t)(ampl/2));
  Serial.print(DpotReg+(uint16_t)(ampl/2));
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT1_SS, HIGH);
  vspi->endTransaction();
}

void FG1_WR(float freq){
  //Serial.print(freq/3);
  //Serial.print('\n');
  vspi->beginTransaction(FGsetting);
  digitalWrite(FG1_SS, LOW);
  delay(100);
  vspi->transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(100);
  digitalWrite(FG1_SS, HIGH);
  delay(100);
  digitalWrite(FG1_SS, LOW);
  delay(100);
  vspi->transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(100);
  digitalWrite(FG1_SS, HIGH);
  vspi->endTransaction();
}

void FG1_ON(){
  vspi->beginTransaction(FGsetting);
  Serial.print(FG1_CTRL);
  digitalWrite(FG1_CTRL, HIGH);
  delay(100);
  digitalWrite(FG1_CTRL, LOW);
  vspi->endTransaction();
}
