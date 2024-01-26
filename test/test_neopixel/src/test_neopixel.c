
/*
 * 24-01-2024 TEST TIRA LED NEOPIXEL
 * recorrido de pixel por pixel, color Rojo
 * recorrido de pixel por pixel, color Verde
 * recorrido de pixel por pixel, color Azul
 * */


/*==================[inclusions]=============================================*/


#include "board.h"
#include <stdint.h>
#include "Neopixel.h"


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

void Blink_Led(); // prototipo

uint8_t num_pixel=1;
struct color rojo = {255,0,0};
struct color verde = {0,255,0};
struct color azul = {0,0,255};
struct color negro = {0,0,0};
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

	while (1){  //bucle principal


		for(num_pixel=1; num_pixel<PIXELS_LENGTH ;num_pixel++){ // recorrido en rojo
			setColor(num_pixel-1,negro);
			setColor(num_pixel,rojo);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(120); //retardo bloqueante 120ms
			setColor(num_pixel,verde);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(120); //retardo bloqueante 120ms
			setColor(num_pixel,azul);
			Neopixel_Update();   //actualiza TIRA LEDS
			delayInaccurateMs(120); //retardo bloqueante 120ms
		}

	}

}

