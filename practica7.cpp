#include <mraa.h>
#include <stdio.h>
#include <stdlib.h>

int temp, hum, res, temperatura;
uint8_t envio[2], t;
mraa_i2c_context i2c;
mraa_aio_context luz;
float lum = 0.0;

int main(void){
		mraa_init();
		i2c = mraa_i2c_init(0);
		mraa_i2c_address(i2c, 0x40);
		luz = mraa_aio_init(0);
		while (1)	{
			printf("Lector de Humedad, Temperatura y Luminisidad\n\n");
			printf("Ingrese el numero de la lectura que desea realizar:\n");
			printf("1)Temperatura\n 2)Humedad\n 3}Luminusidad\n");
			fflush(stdout);
			scanf("%d", &res);
			if (res == 1){
				envio[0] = 0x03;
				envio[1] = 0x11;
				mraa_i2c_write(i2c, envio, 0x02);
				do{
					envio[0] = mraa_i2c_read_byte_data(i2c, 0x00 );
					envio[0] = (envio[0] & 0x01);
					} while (envio[0] != 0);
				mraa_i2c_read_bytes_data(i2c, 0x01, envio, 0x02);
				temperatura = envio[0]*64 + envio[1]/4;
				printf("%d\n",temperatura);
				temperatura = (temperatura/32) - 50;
				printf("\nLa temperatura es de %d grados C\n",temperatura);
			}
			else if (res == 2){
				envio[0] = 0x03;
				envio[1] = 0x01;
				mraa_i2c_write(i2c, envio, 0x02);
				do{
					envio[0] = mraa_i2c_read_byte_data(i2c, 0x00);
					envio[0] = (envio[0] & 0x01);
				} while(envio[0] != 0);
				mraa_i2c_read_bytes_data(i2c, 0x01, envio, 0x02);
				hum = envio[0]*16 + envio[1]/16;
				hum = (hum/16) - 24;
				printf("\nLa humedad es de %d %\n",hum);
			}
			else if(res == 3){
				if(luz == NULL){ return 1;} 
				lum = mraa_aio_read_float(luz);
				printf("\nLa luminusidad es de: %.2f\n", lum);
			}
			else {
				printf("\nOpcion invalida, intentelo de nuevo\n"); 
			}
		fflush(stdin);
		}
		return 0;
}

© 2018 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
API
Training
Shop
Blog
About
