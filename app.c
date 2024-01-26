
/*
 * 24-01-2024 revision Nico v1 - porteo de workspace, firmware, modulos
 * */


/*==================[inclusions]=============================================*/

#include "app.h"
#include "board.h"
#include <stdint.h>
#include "Neopixel.h"
#include "Neopixel_Efects.h"
#include "Touch_ADC.h"

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

//********* variables main ************

struct color cl = {0,MAX_VALUE/2, MAX_VALUE/2}; // color principal - violeta
struct color c2 = {255,5,5}; // color de contraste - verde intenso

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

   TouchADC_Init();
	while (1){  // cada vez que prende el led_integrado, actualiaza los leds
		Neopixel_Wait(); // espera que la tira led termine de actualizar la tira de leds
		Efects_sinoidal_breath_c_mirror(cl); // actualizo el color de toda la tira
		TouchADC_read();  // leo los tactiles
		if( IS_TOUCH() ){
			c2.g=rand()%170;
			c2.r=rand()%170;
			c2.b=rand()%170;
			TouchADC_efects(c2,7); // llamo al efecto color c2, con radio de colision 3
		}

		Neopixel_Update();   //actualiza TIRA LEDS
      Blink_Led();
		delayInaccurateMs(18); //retardo bloqueante 22ms, opcional
	}

}

uint8_t state=0;
void Blink_Led(){
      if(state==ON){ //prende LED1
         state=OFF;
         Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, OFF );
      }
		else{          //apaga LED1
			 state=ON;
			 Chip_GPIO_SetPinState( LPC_GPIO_PORT, 0, 14, ON );
		}
}
