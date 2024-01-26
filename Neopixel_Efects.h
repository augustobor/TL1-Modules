#ifndef _NEOPIXEL_EFECTS_H_
#define _NEOPIXEL_EFECTS_H_

#include "Neopixel.h"

//****** valores configurables ******
#define MAX_VALUE 160      // valor maximo que puede tener un color, sin sobrecargar la bateria


// ***** Efectos disponibles ******

// efecto de onda senoidal de color c, con 15%offset siempre prendido, espejado respecto del centro 
void Efects_sinoidal_breath_c_mirror(struct color c);

// efecto para colision
void Efects_colision(uint8_t pixel_center,struct color cl, uint8_t radius);


#endif /* #ifndef _NEOPIXEL_EFECTS_H_*/
