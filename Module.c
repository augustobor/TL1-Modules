
#include <stdio.h>
#include <inttypes.h>

#define OFF 0
#define ON 1
#define SOUND_LONG 4
#define TRUNC(n) ((uint16_t)(n))

uint8_t sound_raw[SOUND_LONG]; // vetor sonido en crudo
uint8_t sound_module[SOUND_LONG];// vector modulado
uint16_t sound_module_limit=3; // dimension logica del sonido

uint8_t FLAG_crash=OFF;

void print_vector(uint8_t *v,uint16_t limit); // prototipos
void modular(float vt);
void amplificar(float ganancia);
uint8_t interpol(uint8_t y1 ,uint8_t y2, float dx );

int main(){

    sound_raw[0]=100;   // cargo valores de prueba
    sound_raw[1]=128;
    sound_raw[2]=180;
    sound_raw[3]=130;

    print_vector(sound_raw,SOUND_LONG); // imprimo vector original
    modular(1.5);                       // modulo
    print_vector(sound_module,sound_module_limit); // imprimo vector resultado
    amplificar(2);                      // amplifico vector resultado
    print_vector(sound_module,sound_module_limit); // imprimo vector resultado    
    printf("FLAG_crash: %d \n",FLAG_crash);
}

// usa @vt: velocidad de transduccion
// recalcula sound_module y sound_module_limit
void modular(float vt){
    float dx; // variacion x
    uint8_t y1,y2,x;
    
    sound_module_limit=( (((float)SOUND_LONG)/vt)+0.5); // recaolcula la dimension logica
    
    for(int i=0; i<sound_module_limit ; i++){
        x=TRUNC(i*vt); // valor interpolado inferior
        y1=sound_raw[x];
        y2=sound_raw[x+1];
        dx=(i*vt)-x; //distancia entre el valor interpolado inferior, y el valor real a interpolar
        sound_module[i]=interpol(y1,y2,dx);
    }
}

// interpolacion lineal, toma 2 valores , y el porcentaje de cercania entre ellos
uint8_t interpol(uint8_t y1 ,uint8_t y2, float dx ){
    return (y1 + (y2-y1)*dx);
}


// @ganancia cantidad de veces que amplifica respecto al medio de la señal
// si tiene demaciada ganancia habilita el flag de sonido roto
void amplificar(float ganancia){
    uint8_t temp_s;
    float temp_sg;
    for(int i=0; i<sound_module_limit; i++){
        temp_s=sound_module[i];
        temp_sg=(temp_s-128)*ganancia;
        if(temp_sg>128){
            FLAG_crash=ON;  // si tiene demaciada ganancia habilita el flag de sonido roto
            temp_sg=128;
        }
        if(temp_sg<-128){
            FLAG_crash=ON;  // si tiene demaciada ganancia habilita el flag de sonido roto
            temp_sg=-128;
        }
        sound_module[i]= temp_sg + 128; // al valor medio, le suma el delta amplificado
    }
}


void print_vector(uint8_t *v,uint16_t limit){
    printf("[%d]: ",limit);
    printf("%u",v[0]);
    for(int i=1; i<limit; i++){
        printf(", %u",v[i]);
    }
    printf("\n");
}
