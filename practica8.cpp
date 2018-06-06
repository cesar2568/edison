#include <stdio.h>
#include <mraa.h>
#define PB_PIN 5
#define LED_PIN 13
#include <stdlib.h>
#include <time.h> 
#include <ncurses.h>

int stop, reset, on, c=0, seg=0;
mraa_gpio_context PBedison;
mraa_gpio_context ledPin;



int main(void){
	mraa_init();
	PBedison = mraa_gpio_init(PB_PIN);
	ledPin = mraa_gpio_init(LED_PIN);
	mraa_gpio_dir(PBedison, MRAA_GPIO_IN);
	mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
	mraa_gpio_write(ledPin, 0);

	initscr(); 
	cbreak();
	noecho();
	nodelay(stdscr, true); 
	printw("Timer, press the Pb in Edison.\n Press S to stop \n press R to reset\n"); 
	refresh(); 

	while(1){
		on  = mraa_gpio_read(PBedison);
		if((reset = getch()) == 'r'){
			on = 0;
			c = 0;
			printw("Reset timer\n");
			mraa_gpio_write(ledPin, 0);
		}
		while(on == 1){
			if((stop = getch() ) == 's') {
				printw("Counter stopped\n");
				refresh();
				while(1){
					if((stop = getch() ) == 's') {
						printw("counting\n");
						refresh();
						break;
					}
					else if ((reset =getch()) == 'r'){
					       on = 0;
					       c = 0;
					       printw("Reset timer"); 
					       refresh();
					       mraa_gpio_write(ledPin, 0);
					       break;
					}
				}
			}
			else{
				printw("%d seconds\n", c);
				refresh();
				sleep(1);
				c += 1;
				if(c ==  5){
					on = 0;
					c = 0;
					mraa_gpio_write(ledPin, 1);
					printw("Finished\n");
					refresh();
					break;
				}
			}
		}
	}
	return 0;
}

