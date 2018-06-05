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

void LCD_hora()
{
  mraa_i2c_address(i2c,0x3E);
  ins[0]=0x80;
  ins[1]=0x80;
  mraa_i2c_write(i2c,ins,2);
  
  int i=0;
  int h1int=hora/10;
  char h1= h1int+'0';
  int h2int=hora-h1int*10;
  char h2=h2int+'0';
  int m1int = minuto/10;
  char m1= m1int+'0';
  int m2int= minuto-m1int*10;
  char m2= m2int+'0';
  int s1int=segundo/10;
  char s1=s1int+'0';
  int s2int=segundo-s1int*10;
  char s2=s2int+'0';
  char day;
  if(ampm)
  {
    day='p';
  }
  else
  {
    day='a';
  }
  
  char texto1[7]={'H','O','R','A',':','',''};
  char texto2[7]={h1,h2,':',m1,m2,day,'m'};
  while(i<7)
  {
    ins[0]=0x40;
    ins[1]=texto1[i];
    mraa_i2c_write(i2c,ins,2);
    i++;
  }
  ins[0]=0x80;
  ins[1]=0xC0;
  mraa_i2c_write(i2c,ins,2);
  i=0;
  while(i<7)
  {
    ins[0]=0x40;
    ins[1]=texto2[i];
    mraa_i2c_write(i2c,ins,2);
    i++;
  }
}

void Clock()
{
  time_t ahorita;
  ahorita= time(NULL);
  printf("Epoch: %d\n", ahorita);
  
  int yearf=31536000;
  ano= ahorita/yearf+1970;
  int monthf=ahorita%yearf;
  mes=0;
  int x=0;
  int m31=31*24*3600;
  int m30=30*24*3600;
  int m28=28*24*3600;
  monthf=monthf-11*24*3600;
  monthf=monthf-7*3600;
  if(monthf>0)
  {
    mes=1;
    monthf=monthf;
    x=monthf;
  }
  if(monthf>m31)
  {
    mes=2;
    monthf=monthf-m31;
  }
  if(monthf>m28)
  {
    mes=3;
    monthf=monthf-m28;
  }
  if(monthf>m31)
  {
    mes=4;
    monthf=monthf-m31;
  }
  if(monthf>m30)
  {
    mes=5;
    monthf=monthf-m30;
  }
  if(monthf>m31)
  {
    mes=6;
    monthf=monthf-m31;
  }
  if(monthf>m30)
  {
    mes=7;
    monthf=monthf-m30;
  }
  if(monthf>m31)
  {
    mes=8;
    monthf=monthf-m31;
  }
  if(monthf>m31)
  {
    mes=9;
    monthf=monthf-m31;
  }
  if(monthf>m30)
  {
    mes=10;
    monthf=monthf-m30;
  }
  if(monthf>m31)
  {
    mes=11;
    monthf=monthf-m31;
  }
  if(monthf>m30)
  {
    mes=12;
    monthf=monthf-m30;
  }
  dia=monthf/(24*3600);
  int horaf= monthf%(24*3600);
  hora = horaf/3600;
  int minutef=horaf%3600;
  minuto=minutef/60;
  segundo=minutef%60;
  if(hora>12)
  {
    hora=hora-12;
    ampm=1;
    printf("ano: %d, Mes: %d, Dia: %d, Hora: %d, minuto: %d, segundo: %d",ano,mes,dia,hora,minuto,segundo);
  }
  else
  {
    printf("ano: %d, Mes: %d, Dia: %d, Hora: %d, minuto: %d, segundo: %d",ano,mes,dia,hora,minuto,segundo);
    ampm=0;
  }
}

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
