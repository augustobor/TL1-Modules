
/*
 * 24-01-2024 test de modulo Neopixel Efects
 * genera la onda senoidal del efecto durante 5segundos
 * luego 1 segundo de efecto colision en 1er segmento
 * luego 1 segundo de efecto colision en 2er segmento
 * luego 1 segundo de efecto colision en 3er segmento
 * luego 1 segundo de efecto colision en 4er segmento
 * */


/*==================[inclusions]=============================================*/

#include "app.h"
#include "board.h"
#include <stdint.h>
#include "Neopixel.h"
#include "Neopixel_Efects.h"


/*==================[macros and definitions]=================================*/

#define OUTPUT   1
#define INPUT    0

#define ON       1
#define OFF      0
#define INACCURATE_TO_MS       20400


// Delay apropiativo inexacto copia SAPI
void delayInaccurateMs(uint32_t delay_ms){
   volatile uint32_t i;
   volatile uint32_t delay;
   delay = INACCURATE_TO_MS * delay_ms;
   for( i=delay; i>0; i-- );
}


//********* variables main ************

struct color cl = {0,MAX_VALUE/2, MAX_VALUE/2}; // color principal - violeta
struct color c2 = {5,5,205}; // color de contraste - verde intenso
volatile uint8_t delay_refresh=22; // velocidad del refresco de los efectos
uint8_t radius=7;

//********* main ************
int main(void)
{
   Board_Init();
   Neopixel_Init();

   // Configuro LED1 = pin P2_10 = GPIO0[14]
   Chip_SCU_PinMux( 2, 10, SCU_MODE_INACT, SCU_MODE_FUNC0 );
   // Configuro COL1 = pin P0_0 = GPIO3[12]
   Chip_SCU_PinMux( 7, 4, SCU_MODE_INACT, SCU_MODE_FUNC0 );

   // Configuro GPIO0[14] como salida
   Chip_GPIO_SetDir( LPC_GPIO_PORT, 0, (1<<14), OUTPUT );
   // Configuro GPIO0[0] como salida
   Chip_GPIO_SetDir( LPC_GPIO_PORT, 3, (1<<12), OUTPUT );

   // Pongo en estado bajo LED1 el GPIO0[14]
   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, OFF );


	while (1){  // bucle principal

		for(int i=0;i<(5000/delay_refresh);i++){ // repite hasta completar 5 segundos de demora por ejecucion
			Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(delay_refresh); //retardo bloqueante 22ms, opcional
			Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		}

		for(int i=0;i<(1000/delay_refresh);i++){ // repite hasta completar 10 segundos de demora por ejecucion
			Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
			Efects_colision(PIXELS_LENGTH/16,c2,radius);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(delay_refresh); //retardo bloqueante 22ms, opcional
			Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		}

		for(int i=0;i<(1000/delay_refresh);i++){ // repite hasta completar 10 segundos de demora por ejecucion
			Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
			Efects_colision((PIXELS_LENGTH*3)/16,c2,radius);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(delay_refresh); //retardo bloqueante 22ms, opcional
			Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		}

		for(int i=0;i<(1000/delay_refresh);i++){ // repite hasta completar 10 segundos de demora por ejecucion
			Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
			Efects_colision((PIXELS_LENGTH*5)/16,c2,radius);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(delay_refresh); //retardo bloqueante 22ms, opcional
			Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		}

		for(int i=0;i<(1000/delay_refresh);i++){ // repite hasta completar 10 segundos de demora por ejecucion
			Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
			Efects_colision((PIXELS_LENGTH*7)/16,c2,radius);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(delay_refresh); //retardo bloqueante 22ms, opcional
			Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		}

	}

}
