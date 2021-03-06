/*********************************************************************** 
  A library for using the MLX90615 IR Thermometer with the BBC micro:bit

  Designed to work with the 3V version of the sensor:
  https://www.proto-pic.co.uk/infrared-thermometer-MLX90615.html

  The sensors 4 terminals should be connected as follows:
  SDA -> micro:bit pin 20
  SCL -> micro:bit pin 19
  VSS -> micro:bit 0V
  VDD -> micro:bit 3V
  
  For basic use, see example code provided.

  Written by Evan Morgan, School of Informatics, University of Edinburgh 
  Distributed under the MIT Licence - https://opensource.org/licenses/MIT
  Copyright (c) 2016 University of Edinburgh
 *************************************************************************/

#ifndef UBIT_MLX90615_H
#define UBIT_MLX90615_H
 
#include "MicroBit.h"
 
#define MLX90615_I2CADDR 0x5B // default slave address of MLX90615

/* RAM: address values from datasheet 
   https://www.sparkfun.com/datasheets/Sensors/Temperature/SEN-09570-datasheet-3901090614M005.pdf */
#define MLX90615_TA 0x06    // ambient temp
#define MLX90615_TOBJ1 0x07 // object1 temp
#define MLX90615_TOBJ2 0x08 // object2 temp
 
class uBit_MLX90615 {
public:
    uBit_MLX90615(I2C* i2c,uint8_t addr = MLX90615_I2CADDR);
    int getAmbient(void);
    int getObject(void);
  
private:
    I2C* _i2c;  
    int getTemp(uint8_t reg);
    uint8_t _addr;
    uint8_t lsb;
    uint8_t msb;
    uint8_t PEC;
    int temp;
};
 
#endif