
#include "Neopixel_Efects.h"

// ******* valores empiricos calibrados para diferenciar cada aporte de potencial de cada touch
static uint16_t triger_value_t1 = 432; // cada triger es ligeramente inferior al valor nominal de activacion de cada touch
static uint16_t triger_value_t2 = 210; // supone que los sensores tactiles estan conectados en un DAC R2R
static uint16_t triger_value_t3 = 105;
static uint16_t triger_value_t4 = 55; // ?


// ******* Funciones

void TouchADC_Init();  // inicializa el ADC, y los flags
void TouchADC_read();  // lee el ADC y decodifica las banderas de los touch presionados
void TouchADC_efects(struct color cl, uint8_t radius); // cuando se detecta un touch presionado, se genera una auriola de color "c" y radio "r"

