#include <SPI.h>
#include "FG_AD5932.h"
#include "DP_AD5970.h"

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




const float c4=261;
const float d4=293;
const float e4=329;
const float gs4=415;
const float a5=0x94;

//instantiate all the devices
FG_AD5932 FG1(FG1_SS,FG1_CTRL,FG1_STDB);
FG_AD5932 FG2(FG2_SS,FG2_CTRL,FG2_STDB);
FG_AD5932 FG3(FG3_SS,FG3_CTRL,FG3_STDB);

DP_AD5970 DP1(DPOT1_SS);
DP_AD5970 DP2(DPOT2_SS);
DP_AD5970 DP3(DPOT3_SS);

void setup() {
  Serial.begin(115200);
  SPI.begin(VSPI_SCLK,VSPI_MISO,VSPI_MOSI);
  
  pinMode(DPOT1_SS, OUTPUT); //DPOT1_ss
  pinMode(AMP1_EN, OUTPUT); //AMP1_enable
  
  pinMode(DPOT2_SS, OUTPUT); //DPOT2_ss
  pinMode(AMP2_EN, OUTPUT); //AMP2_enable
  
  pinMode(DPOT3_SS, OUTPUT); //DPOT3_ss
  pinMode(AMP3_EN, OUTPUT); //AMP3_enable

  FG1.FGinit();
}



void loop() {
  //write to digipot the peak to peak amplitude . 
  DP1.DPOT_WR(1000);

  //write the frequency to frequency generator C4 is being written
  FG1.FG_WR(c4);

  //Output the frequency 
  FG1.FG_ON();
  
  delay(100);
  
  DP1.DPOT_WR(500);
  
  FG1.FG_WR(e4);
  
  FG1.FG_ON();
  
  delay(100);
  
  DP1.DPOT_WR(800);
  
  FG1.FG_WR(a5);
  
  FG1.FG_ON();
  
  delay(100);
}
