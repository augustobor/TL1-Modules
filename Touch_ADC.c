
#include "Touch_ADC.h"

static uint16_t lectura_adc = 0;	// variable interna para lectura del ADC
static uint8_t flag_touch_1 = 0;    //  vanderas de touch presionado
static uint8_t flag_touch_2 = 0;
static uint8_t flag_touch_3 = 0;
static uint8_t flag_touch_4 = 0;



// ********* lectura_Touch *******
void TouchADC_read(){

	  // Start conversion
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	// Wait for conversion complete
	while(
	  (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT) != SET)
	);

	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &lectura_adc);

	if(lectura_adc>= triger_value_t1){ // si el valor supera el 50%
		lectura_adc-=triger_value_t1; //guardo el valor de las siguientes muestras
		flag_touch_1=ON; // habilito el flag
	}
	if(lectura_adc>= triger_value_t2){ // si lo que le queda supera el triger 2, entoncres esta prendido
		lectura_adc-=triger_value_t2; //guardo el valor de las siguientes muestras
		flag_touch_2=ON; // habilito el flag
	}
	if(lectura_adc>= triger_value_t3){ // si lo que le queda suera el triger 2, entonces habilito el 3er prendido
		lectura_adc-=triger_value_t3; //guardo el valor de las siguientes muestras
		flag_touch_3=ON; // habilito el flag
	}
	if(lectura_adc>= triger_value_t4){ // si lo que le queda suera el triger 2, entonces habilito el 3er prendido
		lectura_adc-=triger_value_t4; //guardo el valor de las siguientes muestras
		flag_touch_4=ON; // habilito el flag
	}
}

void TouchADC_Init(){
    /* Config ADC0 sample mode */
    ADC_CLOCK_SETUP_T ADCSetup = {
       ADC_MAX_SAMPLE_RATE,   // ADC Sample rate:ADC_MAX_SAMPLE_RATE = 400KHz
       10,                    // ADC resolution: ADC_10BITS = 10
       0                      // ADC Burst Mode: (true or false)
    };

	lectura_adc=0;
	flag_touch_1 = 0; //  reset de vanderas
	flag_touch_2 = 0;
	flag_touch_3 = 0;

	Chip_ADC_Init(LPC_ADC0, &ADCSetup);
    /* Disable burst mode */
    Chip_ADC_SetBurstCmd( LPC_ADC0, DISABLE );

	Chip_ADC_SetSampleRate(LPC_ADC0, &ADCSetup, 88000);

	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);


	// deshabilita el resto de los canales
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH1, DISABLE );
    Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH2, DISABLE );
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH2, DISABLE );
    Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH3, DISABLE );
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH3, DISABLE );
    Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH4, DISABLE );
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH4, DISABLE );

}


// *******************
// verifica los flags de touch, y aumenta el brillo correspondiente a los leds cercanos
void TouchADC_efects(struct color cl, uint8_t radius){
	if(radius > (PIXELS_LENGTH/6)-1 ){
		radius=(PIXELS_LENGTH/6)-1;
	}
	if(radius<1){
		radius=1;
	}
	if(flag_touch_1){
		efect_colision(PIXELS_LENGTH/16,cl,radius);
		flag_touch_1=OFF;
	}
	if(flag_touch_2){
		efect_colision(PIXELS_LENGTH*3/16,cl,radius);
		flag_touch_2=OFF;
	}
	if(flag_touch_3){
		efect_colision(PIXELS_LENGTH*5/16,cl,radius);
		flag_touch_3=OFF;
	}
	if(flag_touch_4){
		efect_colision(PIXELS_LENGTH*7/16,cl,radius);
		flag_touch_4=OFF;
	}
}
