
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
   float desfazaje_by_pixel=6.2831853; // longitud_de_onda;
   float corrimiento_angular = 0.0;
   float angulo_temporal;


// efecto de onda senoidal de color c, con 15%offset siempre prendido, espejado respecto del centro 
uint8_t brain_cicle_intensity(uint16_t angule){
  angule=angule%360;
  return brain_table[angule];
}

void Efects_sinoidal_breath_c_mirror(struct color c){
   angulo_temporal+=velocity; // angulo temporal de ese frame, se suma la velocidad deseada en grados por frame
   if(angulo_temporal>360){
    angulo_temporal-=360;
   }

   for(int pix_i=0; pix_i< ((PIXELS_LENGTH - 1)/2) ;pix_i++){ // recorro la mitad de los pixeles
      corrimiento_angular+=desfazaje_by_pixel; // a cada pixel se le asigna un pequeño corrimiento para hacer el efecto desplazamiento-barrido de la onda
      setColor_i(pix_i,c,brain_cicle_intensity(angulo_temporal +corrimiento_angular)); // le asigno al pixel i el color seteado escalado en seno
      mirror(pix_i); // espejado
	}
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
