#include <ncurses.h> 
#include <stdio.h>
#include <time.h>
#include <mraa.h>
#include <string>
#include <stdlib.h> 

#define LED_PIN 13
#define SW_PIN 5

//using namespace std;
int contador = 0, c = 0, reset, on, event, con;
bool ton;
uint8_t ins[2]; 
std::string constring;
mraa_gpio_context ledPin;
mraa_gpio_context PushB;
mraa_i2c_context i2c;

void LCD_init();
void SetBGColor(int red, int blue, int green);
void LCD_home();
void LCD_write(std::string msg);
void LCD_clear();

int main(void)
{
  mraa_init();
  ledPin = mraa_gpio_init(LED_PIN);
  PushB = mraa_gpio_init(SW_PIN);
  mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
  mraa_gpio_dir(PushB, MRAA_GPIO_IN);
  mraa_gpio_write(ledPin, 0);
  i2c = mraa_i2c_init(0);
  mraa_i2c_address(i2c, 0x3E);
  
  LCD_init();
  SetBGColor(255,255,250);
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  printw("Contador, press s to start\n Push button	plus one \n Reset: tecla r\n");
  refresh();
  LCD_write("Hola");
	
	while(1)
	{
		if((on = getch()) == 's') 
		{
			ton = true;
			printw("Encendido\n");
			refresh();
			LCD_clear();
			LCD_home();
			LCD_write(   "Encendido");
		}
		if((reset = getch()) == 'r') {
			ton = false;
			contador = 0;
			LCD_clear();
			printw("Reinicio\n");
			refresh();
			LCD_home();
			LCD_write("Reinicio");
			mraa_gpio_write(ledPin, 0);
			}
		while(on == 1)
		{
			if((reset = getch()) == 'r') {
			ton = false;
			contador = 0;
			LCD_clear();
			printw("Reinicio\n");
			refresh();
			LCD_home();
			LCD_write("Reinicio");
			mraa_gpio_write(ledPin,0);
			}
			if(mraa_gpio_read(PushB))
			{
				while(mraa_gpio_read(PushB));
				contador++;
				printw("Contador %d\n", contador);
				refresh();
				ins[0] = 0x80;
				ins[1] = 0xC0;
				mraa_i2c_write(i2c, ins, 2);
				LCD_write("Contador ");
				con = contador + 48;
				constring = con;
				LCD_write(constring);
			}
			else if(contador == 10)
			{
				printw("Contador al maximo\n");
				refresh();
				mraa_gpio_write(ledPin, 1);
				ton = 0;
				ins[0] = 0x80;
				ins[1] = 0x10;
				for(int i = 0; i<10; i++){mraa_i2c_write(i2c,ins,2);}
				LCD_write("Contador");
				LCD_write(" Max.");
			}
			}
		}
		return 0;
	}

void  LCD_init(){
  usleep(1);
  ins[0] = 0x80;
  ins[1] = 0x3C;
  for(int i = 0; i == 3; i++)
  {
	  mraa_i2c_write(i2c, ins, 2);
	  usleep(2);
  }
  ins[1] = 0x08;
  mraa_i2c_write(i2c, ins, 2);
  usleep(1);
  ins[1] = 0x0C;
  mraa_i2c_write(i2c, ins, 2);
  usleep(1);
  ins[1] = 0x06;
  mraa_i2c_write(i2c, ins, 2);
  usleep(1);
  ins[1] = 0x01;
  mraa_i2c_write(i2c, ins, 2);
}

void  SetBGColor(int red, int blue, int green){
	ins[0] = 0x00;
	ins[2] = 0x00;
	mraa_i2c_address(i2c, 0x62);
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
	ins[0] = 0x08;
	ins[1] = 0xFF;
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
	ins[0] = 0x01;
	ins[1] = 0x00;
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
	ins[0] = 0x02;
	ins[1] = blue;
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
	ins[0] = 0x03;
	ins[1] = green;
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
	ins[0] = 0x04;
	ins[1] = red;
	mraa_i2c_address(i2c, 0x3E);
}

void  LCD_home() {
	ins[0] = 0x80;
	ins[1] = 0x02;
	mraa_i2c_write(i2c, ins, 2);
	usleep(100);
}

void LCD_clear() {
	ins[0] = 0x80;
	ins[1] = 0x01;
	mraa_i2c_write(i2c, ins, 2);
	usleep(1);
}

void LCD_write(std::string msg)
{
  int l = msg.length();
  for( int i = 0; i<l; i++) {
	  ins[0] = 0x40;
	  ins[1] = msg.at(i);
	  mraa_i2c_write(i2c, ins, 2);
  }
}	
