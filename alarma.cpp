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
mraa_gpio_context aceptar; //enter
mraa_gpio_context led; //ledpin
int arriban=0; //arribaint
int abajon=0; //abajoint
int aceptarn=0; //enterInt
int ledn=0; //ledInt
int horaalarma=0; //alarmhour
int minalarma=0; //alarmMinute
bool ampmalarma=0; //alarmAmpm
bool listo=0; //ready
bool sonido=0; //sonando

void menu()
{
  do
  {
    LCD_alarma();
    arriban=mraa_gpio_read(arriba);
    if(arriban==1)
    {
      while(arriban==1)
      {
        arriban=mraa_gpio_read(arriba);
      }
      horaalarma=horaalarma+1;
      if(horaalarma>12)
      {
        horaalarma=0;
      }
    }
    abajon=mraa_gpio_read(abajo);
    if(abajon==1)
    {
      while(abajon==1)
      {
        abajon=mraa_gpio_read(abajo);
      }
      horaalarma=horaalarma-1;
      if(horaalarma<0)
      {
        horaalarma=12;
      }
    }
    aceptarn=mraa_gpio_read(aceptar);
  }while(aceptarn!=1);
  while(aceptarn==1)
  {
    aceptarn=mraa_gpio_read(aceptar);
  }
  do
  {
    LCD_alarma();
    arriban=mraa_gpio_read(arriba);
    if(arriban==1)
    {
      while(arriban==1)
      {
        arriban=mraa_gpio_read(arriba);
      }
      minalarma=minalarma+1;
      if(minalarma>59)
      {
        minalarma=0;
      }
    }
    abajon=mraa_gpio_read(abajo);
    if(abajon==1)
    {
      while(abajon==1)
      {
        abajon=mraa_gpio_read(abajo);
      }
      minalarma=minalarma-1;
      if(minalarma<0)
      {
        minalarma=59;
      }
    }
    aceptarn=mraa_gpio_read(aceptar);
  }while(aceptarn!=1);
  while(aceptarn==1)
  {
    aceptarn=mraa_gpio_read(aceptar);
  }
  do
  {
    LCD_alarma();
    arriban=mraa_gpio_read(arriba);
    if(arriban==1)
    {
      while(arriban==1)
      {
        arriban=mraa_gpio_read(arriba);
      }
      ampmalarma= !ampmalarma;
    }
    abajon=mraa_gpio_read(abajo); //posible fallo
    if(abajon==1)
    {
      while(abajon==1)
      {
        abajon=mraa_gpio_read(abajo);
      }
      ampmalarma=!ampmalarma;
    }
    aceptarn=mraa_gpio_read(aceptar);    
  }while(aceptarn);//aqui finaliza do
  while(aceptarn==1)
  {
    aceptarn=mraa_gpio_read(aceptar);
  }
}//finaliza menu

void LCD_alarma() //mandaralarma
{
  mraa_i2c_address(i2c, 0x3E);
  ins[0]=0x80;
  ins[1]=0x80;
  mraa_i2c_write(i2c,ins,2);
  int i=0;
  int h1int=horaalarma/10;
  char h1=h1int+'0';
  int h2int=horaalarma-h1int*10;
  char h2=h2int+'0';
  int m1int = minalarma/10;
  char m1= m1int+'0';
  int m2int= minalarma-m1int*10;
  char m2= m2int+'0';
  char day;
  if(ampmalarma)
  {
    day='p';
  }
  else
  {
    day='a';
  }
  char texto1[7]={'A','L','A','R','M','A',':'};
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
}//finaliza LCD_alarma

void LCD_hora() //mandarHora
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
}//finaliza LCD_alarma

void Clock() //obternetTiempo
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
}//finaliza clock

void LCD_Start() //initLCD
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
}//finaliza LCD_Start
