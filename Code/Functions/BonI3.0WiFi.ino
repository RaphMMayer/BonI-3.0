#include <SPI.h>
#include "BluetoothSerial.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define VSPI_MISO   32
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

//WiFiServer server(80);
BluetoothSerial SerialBT;
//wifi name and password



//const char* ssid = "BonI3.0";
//const char* password = "BonI";
const uint16_t FsLSBReg=0xC000;//frequency start register of AD5932 LSB
const uint16_t FsMSBReg=0xD000;//frequency start register of AD5932 MSB



//uninitalised pointers to SPI objects
SPIClass *vspi = NULL;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("BonI3.0"); //Bluetooth device name
  SerialBT.setTimeout(1);
  Serial.println("The device started, now you can pair it with bluetooth or connect to its WiFi!");
//  Serial.println("Configuring access point...");
//  WiFi.softAP(ssid, password);
//  IPAddress myIP = WiFi.softAPIP();
//  Serial.print("AP IP address: ");
//  Serial.println(myIP);
//  server.begin();
  Serial.println("Server started");
  while(Serial.read()>= 0){}//clear serialport
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


  DPOTinit();
  FGinit();
  
}

SPISettings FGsetting(8000000, MSBFIRST, SPI_MODE2);
SPISettings DPOTsetting(1000000, MSBFIRST, SPI_MODE1);


void loop() {
//  WiFiClient client = server.available(); 
//   if (client) {                             // if you get a client,
//    Serial.println("New Client.");           // print a message out the serial port
//    while (client.connected()){
//      if (!client.connected()){
//        Serial.print("connection lost");
//      }
//  else if (client.available()){
//    int Reg1 =client.parseInt();
//    int adata =client.parseInt();
//    int fdata =client.parseInt();
//    int tdata =client.parseInt();
//    
//    Serial.print("The first register is: ");
//    Serial.print(Reg1,HEX);
//    Serial.println();
//
//
//    Serial.print("The Amplitude is: ");
//    Serial.print(adata);
//    Serial.println();
//    
//    Serial.print("The frequency  is: ");
//    Serial.print(fdata);
//    Serial.println();
//    
//    Serial.print("The time is: ");
//    Serial.print(tdata);
//    Serial.println();
//
//    switch(Reg1){
//      case 0:
//        if (adata==1){
//          FG1_STB(0);
//          digitalWrite(AMP1_EN, LOW);//turn on the amplifier
//
//        }
//        else if (adata==0){
//          FG1_STB(1);
//          digitalWrite(AMP1_EN, HIGH);//turn on the amplifier
//        }
//
//        if (fdata==1){
//          FG2_STB(0);
//          digitalWrite(AMP2_EN, LOW);//turn on the amplifier
//
//        }
//        else if(fdata==0) {
//          FG2_STB(1);
//          digitalWrite(AMP2_EN, HIGH);//turn on the amplifier
//        }
//
//        if (tdata==1){
//          FG3_STB(0);
//          digitalWrite(AMP3_EN, LOW);//turn on the amplifier
//
//        }
//        else if(tdata==0){
//          FG3_STB(1);
//          digitalWrite(AMP3_EN, HIGH);//turn on the amplifier
//        }
//      break;
//
//        
//      //check location of device written to: 1 for top,2 for middle and 3 for bottom
//      case 1:
//        DPOT1_WR(adata);
//        FG1_STB(0);
//        FG1_WR(fdata);
//        digitalWrite(AMP1_EN, LOW);//turn on the amplifier
//        FG1_ON();
//        if (tdata>0){
//        delay(tdata);
//        FG1_STB(1);
//        digitalWrite(AMP1_EN, HIGH);//turn off the amplifier
//        }
//        break;
//      case 2:
//        DPOT2_WR(adata);
//        FG2_STB(0);
//        FG2_WR(fdata);
//        digitalWrite(AMP2_EN, LOW);//turn on the amplifier
//        FG2_ON();
//        if (tdata>0){
//        delay(tdata);
//        FG2_STB(1);
//        digitalWrite(AMP2_EN, HIGH);//turn off the amplifier
//        }
//        break;
//      case 3:
//        DPOT3_WR(adata);
//        FG3_STB(0);
//        FG3_WR(fdata);
//        digitalWrite(AMP3_EN, LOW);//turn on the amplifier
//        FG3_ON();
//        if (tdata>0){
//        delay(tdata);
//        FG3_STB(1);
//        digitalWrite(AMP3_EN, HIGH);//turn off the amplifier
//        }
//        break; 
//  }
//  }
//   }
//    
//   }
//  else 
if (SerialBT.available()) {
    int Reg1 =SerialBT.parseInt();
    int adata =SerialBT.parseInt();
    int fdata =SerialBT.parseInt();
    int tdata =SerialBT.parseInt();
    
    Serial.print("The first register is: ");
    Serial.print(Reg1,HEX);
    Serial.println();


    Serial.print("The Amplitude is: ");
    Serial.print(adata);
    Serial.println();
    
    Serial.print("The frequency  is: ");
    Serial.print(fdata);
    Serial.println();
    
    Serial.print("The time is: ");
    Serial.print(tdata);
    Serial.println();

    switch(Reg1){
      case 0:
        if (adata==1){
          FG1_STB(0);
          digitalWrite(AMP1_EN, LOW);//turn on the amplifier

        }
        else if (adata==0){
          FG1_STB(1);
          digitalWrite(AMP1_EN, HIGH);//turn on the amplifier
        }

        if (fdata==1){
          FG2_STB(0);
          digitalWrite(AMP2_EN, LOW);//turn on the amplifier

        }
        else if(fdata==0) {
          FG2_STB(1);
          digitalWrite(AMP2_EN, HIGH);//turn on the amplifier
        }

        if (tdata==1){
          FG3_STB(0);
          digitalWrite(AMP3_EN, LOW);//turn on the amplifier

        }
        else if(tdata==0){
          FG3_STB(1);
          digitalWrite(AMP3_EN, HIGH);//turn on the amplifier
        }
      break;

        
      //check location of device written to: 1 for top,2 for middle and 3 for bottom
      case 1:
        DPOT1_WR(adata);
        FG1_STB(0);
        FG1_WR(fdata);
        digitalWrite(AMP1_EN, LOW);//turn on the amplifier
        FG1_ON();
        if (tdata>0){
        delay(tdata);
        FG1_STB(1);
        digitalWrite(AMP1_EN, HIGH);//turn off the amplifier
        }
        break;
      case 2:
        DPOT2_WR(adata);
        FG2_STB(0);
        FG2_WR(fdata);
        digitalWrite(AMP2_EN, LOW);//turn on the amplifier
        FG2_ON();
        if (tdata>0){
        delay(tdata);
        FG2_STB(1);
        digitalWrite(AMP2_EN, HIGH);//turn off the amplifier
        }
        break;
      case 3:
        DPOT3_WR(adata);
        FG3_STB(0);
        FG3_WR(fdata);
        digitalWrite(AMP3_EN, LOW);//turn on the amplifier
        FG3_ON();
        if (tdata>0){
        delay(tdata);
        FG3_STB(1);
        digitalWrite(AMP3_EN, HIGH);//turn off the amplifier
        }
        break; 
    }
  }
  }
void FGinit(){
  vspi->beginTransaction(FGsetting);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG1_SS, HIGH);
  delay(1);

  //FG2
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG2_SS, HIGH);
  delay(1);

//FG3
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0xED3); //Initialize setting
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0x63E8);//Period of increment=1000
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0x2000);//LSB increment frequency=0
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0x3000);//MSB increment frequency=0
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0x1002);//Increment step=2(minimum)
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0xC000);// LSB initialize frequency(0)
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(0xD000);// MSB initialize frequency(0)
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  
  vspi->endTransaction();
}

void DPOTinit(){
  vspi->beginTransaction(DPOTsetting);
  digitalWrite(DPOT1_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x1C03);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT1_SS, HIGH);

  digitalWrite(DPOT2_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x1C03);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT2_SS, HIGH);

  digitalWrite(DPOT3_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x1C03);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT3_SS, HIGH);
  vspi->endTransaction();
}
void DPOT1_WR(int ampl) {
  // take the SS pin low to select the chip:
  vspi->beginTransaction(DPOTsetting);

  digitalWrite(DPOT1_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x0400+ampl/2);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT1_SS, HIGH);
  vspi->endTransaction();
}

void DPOT2_WR(int ampl) {
  // take the SS pin low to select the chip:
  vspi->beginTransaction(DPOTsetting);

  digitalWrite(DPOT2_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x0400+ampl/2);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT2_SS, HIGH);
  vspi->endTransaction();
}

void DPOT3_WR(int ampl) {
  vspi->beginTransaction(DPOTsetting);

  digitalWrite(DPOT3_SS, LOW);
  delay(10);
  //  send in the address and value via SPI:
  vspi->transfer16(0x0400+ampl/2);
  delay(10);
  // take the SS pin high to de-select the chip:
  digitalWrite(DPOT3_SS, HIGH);
  vspi->endTransaction();
}
void FG1_WR(int freq){
  //Serial.print(freq/3);
  //Serial.print('\n');
  vspi->beginTransaction(FGsetting);
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(1);
  digitalWrite(FG1_SS, HIGH);
  delay(1);
  digitalWrite(FG1_SS, LOW);
  delay(1);
  vspi->transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(1);
  digitalWrite(FG1_SS, HIGH);
  vspi->endTransaction();
}
void FG2_WR(int freq){
  //Serial.print(freq/3);
  //Serial.print('\n');
  vspi->beginTransaction(FGsetting);
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(1);
  digitalWrite(FG2_SS, HIGH);
  delay(1);
  digitalWrite(FG2_SS, LOW);
  delay(1);
  vspi->transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(1);
  digitalWrite(FG2_SS, HIGH);
  vspi->endTransaction();
}
void FG3_WR(int freq){
  //Serial.print(freq/3);
  //Serial.print('\n');
  vspi->beginTransaction(FGsetting);
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));//12 bits LSB of the data
  Serial.print(FsLSBReg+FLSB((uint32_t)round(freq/0.001953)));
  delay(1);
  digitalWrite(FG3_SS, HIGH);
  delay(1);
  digitalWrite(FG3_SS, LOW);
  delay(1);
  vspi->transfer16(FsMSBReg+FMSB((uint32_t)round(freq/0.001953)));//12 bits MSB of the data
  delay(1);
  digitalWrite(FG3_SS, HIGH);
  vspi->endTransaction();
}

void FG1_ON(){
  Serial.print(FG1_CTRL);
  digitalWrite(FG1_CTRL, HIGH);
  delay(1);
  digitalWrite(FG1_CTRL, LOW);
}
void FG2_ON(){
  Serial.print(FG2_CTRL);
  digitalWrite(FG2_CTRL, HIGH);
  delay(1);
  digitalWrite(FG2_CTRL, LOW);
}
void FG3_ON(){
  Serial.print(FG3_CTRL);
  digitalWrite(FG3_CTRL, HIGH);
  delay(1);
  digitalWrite(FG3_CTRL, LOW);
}

void FG1_STB(int xx){
  Serial.print(FG1_STDB);
  if(xx==1){
  digitalWrite(FG1_STDB, HIGH);
  }
  else{
  digitalWrite(FG1_STDB, LOW);
  }
}
void FG2_STB(int xx){
  Serial.print(FG2_STDB);
  if(xx==1){
  digitalWrite(FG2_STDB, HIGH);
  }
  else{
  digitalWrite(FG2_STDB, LOW);
  }
}
void FG3_STB(int xx){
  Serial.print(FG3_STDB);
  if(xx==1){
  digitalWrite(FG3_STDB, HIGH);
  }
  else{
  digitalWrite(FG3_STDB, LOW);
  }
}
