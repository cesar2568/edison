#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <mraa.h>

int ano, mes, dia, hora, minuto, segundo;
bool ampm=0;
uint8_t ins[2]; 
mraa_i2c_context i2c;
mraa_gpio_context arriba;
mraa_gpio_context abajo;
mraa_gpio_context aceptar;
mraa_gpio_context led;
int arriban=0;
int abajon=0;
int aceptarn=0;
int ledn=0;
int horaalarma=0;
int minalarma=0;
bool ampmalarma=0;
bool listo=0;
bool sonido=0;

void LCD_Start()
{
  int i=0;
  usleep(3);
  i2c=mraa_i2c_init(0);
  mraa_i2c_address(i2c, 0x3E);
  ins[0]=0x80;
  ins[1]=0x3c;
  usleep(2);
  while(i<=3)
  {
    mraa_i2c_write(i2c,ins,2);
    i++;
    usleep(1);
  }
  ins[1]=0x0E;
  mraa_i2c_write(i2c,ins,2);
  ins[1]=0x01;
  mraa_i2c_write(i2c,ins,2);
  ins[1]=0x06;
  mraa_i2c_write(i2c,ins,2);
  ins[1]=0x02;
  mraa_i2c_write(i2c,ins,2);
  mraa_i2c_address(i2c, 0x62);
  ins[0]=0x00;
  ins[1]=0x20;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x08;
  ins[1]=0xFF;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x01;
  ins[1]=0x00;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x04;
  ins[1]=255;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x03;
  ins[1]=255;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x02;
  ins[1]=255;
  mraa_i2c_write(i2c,ins,2);
  ins[0]=0x06;
  ins[1]=255;
  mraa_i2c_write(i2c,ins,2);
}
