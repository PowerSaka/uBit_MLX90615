/*********************************************************************** 
  A library for using the MLX90615 IR Thermometer with the BBC micro:bit

  Designed to work with the 3V version of the sensor:
  https://www.proto-pic.co.uk/infrared-thermometer-mlx90615.html

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
 
#include "uBit_MLX90615.h"

uBit_MLX90615::uBit_MLX90615(I2C* i2c,uint8_t i2caddr) {
  _addr = i2caddr;
  _i2c = i2c;
}

int uBit_MLX90615::getAmbient(void) {
  return getTemp(MLX90615_TA);
}

int uBit_MLX90615::getObject(void) {
  return getTemp(MLX90615_TOBJ1);
}

int uBit_MLX90615::getTemp(uint8_t reg) {
  char buf[3] = {reg};
  _i2c->write(MLX90615_I2CADDR<<1, buf, 1,true);
  _i2c->read(MLX90615_I2CADDR<<1, buf,2,true);
  lsb=buf[0];
  msb=buf[1];
  temp = ( lsb| (msb << 8));
  temp *= 2;
  temp -= 27315;
  return temp;
}

extern MicroBit uBit;

/**
* Location of temperature
*/
enum TemperatureLocation {
    Object,
    Ambient
};

/**
* Functions to support the MLX90615 sensor
*/
//% 
namespace mlx90615 {
    /**
    * Reads the temperature from the IR sensor MLX90615
    */
    //% blockId=mlx90615 block="temperature %loc"
    int temperature(TemperatureLocation loc) {
        uBit_MLX90615 sensor(&uBit.i2c);
        switch(loc) {
            case TemperatureLocation::Ambient:
                return sensor.getAmbient();
            default:
                return sensor.getObject();
        }
    }
}
