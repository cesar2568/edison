#include <stdio.h>
#include <mraa.h>
#define PB_PIN 5
#define LED_PIN 13
#include <stdlib.h>
#include <time.h> 
#include <ncurses.h>

int PBstop, PBreset, on, c=0, seg=0;
mraa_gpio_context PBedison;
mraa_gpio_context ledPin;



int main(void){
	mraa_gpio_context gpio;
	mraa_init();
	PBedison = mraa_gpio_init(PB_PIN);
	ledPin = mraa_gpio_init(LED_PIN);
	mraa_gpio_dir(PBedison, MRAA_GPIO_IN);
	mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
	mraa_gpio_write(ledPin, 0);

	initscr(); // Inicia ncurses creando una pantalla 
	cbreak();
	noecho();
	nodelay(stdscr, true); //no espera al llegar a getch, para no detener el programa
	printw("Timer, oprimir boton en Edison para comenzar.\n Tecla a = PBStop\n Tecla r = PBreset\n"); 
	refresh(); //la pantalla creada debe ser refrescada para mostrar los cambios 

	while(1){
		on  = mraa_gpio_read(PBedison);
		if((PBreset = getch()) == 'r'){
			on = 0;
			c = 0;
			printw("Reset del timer\n");
			mraa_gpio_write(ledPin, 0);
		}
		while(on == 1){
			if((PBstop = getch() ) == 'a') {
				printw("Conteo detenido\n");
				refresh();
				while(1){
					if((PBstop = getch() ) == 'a') {
						printw("Reanuda conteo");
						refresh();
						break;
					}
					else if ((PBreset =getch()) == 'r'){
					       on = 0;
					       c = 0;
					       printw("Reset del timer"); 
					       refresh();
					       mraa_gpio_write(ledPin, 0);
					       break;
					}
				}
			}
			else{
				printw("%d segundos\n", c);
				refresh();
				sleep(1);
				c += 1;
				if(c ==  5){
					on = 0;
					c = 0;
					mraa_gpio_write(ledPin, 1);
					printw("Cuenta terminada\n");
					refresh();
					break;
				}
			}
		}
	}
	return 0;
}

