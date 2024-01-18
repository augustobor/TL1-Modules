
#include "Neopixel.h"
#include "Neopixel_Efects.h"


// ************** Variables glovales de los Efectos Neopixel *******
#define DESC 1 // descendente
#define ASC 0 // ascendente

volatile int16_t value_rampa;
volatile uint8_t rising_cicle=ASC;
volatile float velocity = 3; // valor positivo o negativo

volatile float value_cicle;
volatile float value_sin;
volatile float value_medio;
volatile uint8_t value_pixel;

volatile uint16_t delay_time=16;


// efecto onda senoidal,
   float longitud_de_onda = 40;
   float desfazaje_by_pixel=6.2831853/ longitud_de_onda;
   float corrimiento_angular;
   float angulo_temporal;

// efecto de onda senoidal de color c, con 15%offset siempre prendido, espejado respecto del centro 
void Efects_sinoidal_breath_c_mirror(struct color c){
   angulo_temporal=((6.2831853*((uint8_t)value_cicle))/1000); // angulo que varia con el tiempo para todos los pixeles (entre 2PI y 0)

   for(int pix_i=0; pix_i< (PIXELS_LENGTH-1/2) ;pix_i++){ // recorro la mitad de los pixeles
         corrimiento_angular=pix_i*desfazaje_by_pixel;
                     // calculo el seno de { 2PI (valor/255) + desfazaje_alineal_del_pixel }
			value_sin = arm_sin_f32( angulo_temporal +corrimiento_angular);
			value_sin+=1; // valor entre 0 y 2
			value_sin= value_sin*0.85 + 0.15*(2); // offset del 15% siempre prendido

         setColor_i(pix_i,c,value_sin/2); // le asigno al pixel i el color seteado escalado en seno
         mirror(pix_i); // espejado
	}
	value_cicle=fmod( (value_cicle+velocity+1000), 1000) ; // revalsa automaticamente , limitado a 1000
}

// efecto para colision
void Efects_colision(uint8_t pixel_center,struct color cl, uint8_t radius){
	setColor( pixel_center,cl);
	mirror(pixel_center);
	for(int i=1;i<radius;i++){
		setColor_fade(pixel_center-i , cl, getColor((PIXELS_LENGTH/6)-i), (((float)radius-i)/radius)); // asigno el color al pixel anterior
		setColor_fade(pixel_center+i , cl, getColor((PIXELS_LENGTH/6)-i), (((float)radius-i)/radius)); // asigno el color del pixel siguiente
		// mirrorles
		mirror(pixel_center-i);
		mirror(pixel_center+i);
	}
}