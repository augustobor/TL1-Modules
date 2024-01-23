
// ************** Includes *****************
#include <stdint.h>
#include <chip.h>
#include <board.h>

// ************** Parametros de la tira led *****************
#define PIXELS_LENGTH 111  // cantidad de leds

typedef struct {
    // Otros registros del puerto GPIO
    uint8_t SET[32];  // Conjunto de registros para establecer bits específicos
    uint8_t CLR[32];  // Conjunto de registros para establecer bits específicos
    // Otros registros del puerto GPIO
} LPC_GPIO_PORT_type;

//************ Estructura de datos de color
   struct color {
      uint8_t g;
      uint8_t r;
      uint8_t b;
   };

//********************

void Neopixel_Init(); // inicializa libreria
void Neopixel_Update();// actualiza el estado de la tira led
void Neopixel_Wait(); // espera a que se termine de actualizar los colores de la tira

void SysTick_Handler(void); // rutina de atencion de interrupciones

struct color getColor(uint8_t number_pixel); // retorna el color del pixel
void setColor(uint8_t number_pixel, struct color c); // asigna el color c al pixel
void setColor_i(uint8_t number_pixel ,struct color c ,float intensity); // asigna una el color "c" al pixel "n" con la "intencidad" espesificada (entre 0 a 1)
void setColor_fade(uint8_t number_pixel, struct color c1, struct color c2, float proportion); //asigna una mescla lineal de los colores "c1" y "c2" al pixel "n", con una "proporcion" espesificada (entre 0 a 1)
void mirror(); // copia espejada de todos los pixeles de la tira led




