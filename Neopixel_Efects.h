
#include "Neopixel.h"

//****** valores configurables ******
#define MAX_VALUE 160      // valor maximo que puede tener un color, sin sobrecargar la bateria


//****** Vector senoidal para neopizel_efects_sinoidal ******
uint8_t brain_table[] = { // tabla de efectos angular, [0..359]
  142, 144, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 178, 180, 182, 184, 186, 188, 189, 191, 193, 195, 197, 198, 200, 202, 203, 205, 207, 208, 210, 211, 213, 214, 216, 217, 219, 220, 222, 223, 225, 226, 227, 228, 230, 231, 232, 233, 234, 236, 237, 238, 239, 240, 241, 242, 243, 244, 244, 245, 246, 247, 247, 248, 249, 249, 250, 251, 251, 252, 252, 253, 253, 253, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 254, 253, 253, 253, 252, 252, 251, 251, 250, 249, 249, 248, 247, 247, 246, 245, 244, 244, 243, 242, 241, 240, 239, 238, 237, 236, 234, 233, 232, 231, 230, 228, 227, 226, 225, 223, 222, 220, 219, 217, 216, 214, 213, 211, 210, 208, 207, 205, 203, 202, 200, 198, 197, 195, 193, 191, 189, 188, 186, 184, 182, 180, 178, 177, 175, 173, 171, 169, 167, 165, 163, 161, 159, 157, 155, 153, 151, 149, 147, 145, 144, 142, 140, 138, 136, 134, 132, 130, 128, 126, 124, 122, 120, 118, 116, 114, 112, 110, 108, 106, 105, 103, 101,  99,  97,  95,  94,  92,  90,  88,  87,  85,  83,  81,  80,  78,  76,  75,  73,  72,  70,  69,  67,  66,  64,  63,  61,  60,  59,  57,  56,  55,  53,  52,  51,  50,  49,  47,  46,  45,  44,  43,  42,  41,  40,  40,  39,  38,  37,  36,  36,  35,  34,  34,  33,  32,  32,  31,  31,  31,  30,  30,  29,  29,  29,  29,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  29,  29,  29,  29,  30,  30,  31,  31,  31,  32,  32,  33,  34,  34,  35,  36,  36,  37,  38,  39,  40,  40,  41,  42,  43,  44,  45,  46,  47,  49,  50,  51,  52,  53,  55,  56,  57,  59,  60,  61,  63,  64,  66,  67,  69,  70,  72,  73,  75,  76,  78,  80,  81,  83,  85,  87,  88,  90,  92,  94,  95,  97,  99, 101, 103, 105, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140
};

// ***** Efectos disponibles ******

// efecto de onda senoidal de color c, con 15%offset siempre prendido, espejado respecto del centro 
void Efects_sinoidal_breath_c_mirror(struct color c);

// efecto para colision
void Efects_colision(uint8_t pixel_center,struct color cl, uint8_t radius);

