#include <mraa.h>
#include <stdio.h>
#include <stdlib.h>

int hum, ans, temperatura;
uint8_t envio[2], t;
mraa_i2c_context i2c;
mraa_aio_context light;
float lum = 0.0;

int main(void){
		mraa_init();
		i2c = mraa_i2c_init(0);
		mraa_i2c_address(i2c, 0x40);
		light = mraa_aio_init(0);
		while (1)	{
			printf("Ingrese el numero de la lectura que desea realizar:\n");
			printf("1.-Temperatura\n 2.-Humedad\n 3.-Luminusidad\n");
			fflush(stdout);
			scanf("%d", &ans);
			if (ans == 1){
				print("si entro");
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
				printf("\nLa temperatura es de %d °C\n",temperatura);
			}
			else if (ans == 2){
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
			else if(ans == 3){
				if(light == NULL){ return 1;} 
				lum = mraa_aio_read_float(light);
				printf("\nLa luminusidad es de: %.2f\n", lum);
			}
			else {
				printf("\nOpcion invalida, intentelo de nuevo\n"); 
			}
		fflush(stdin);
		}
		return 0;
}
