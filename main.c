#include "lib/include.h"
#include <stdio.h>
uint32_t adc[10];

int main(void)
{
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj 50MHZ
    Configurar_GPIO();
    Configurar_UART0();
    CONFIGURACION_ADC();
    CONFIGURACION_ADC_Seq();
    
    unsigned int entrada_adc;
    uint32_t lectura_0;
    uint32_t lectura_1;
    uint32_t lectura_2;
    uint32_t lectura_3;
    uint32_t lectura_4;
    uint32_t lectura_5;

    char cambio_0[4];
    char cambio_1[4];
    char cambio_2[4];
    char cambio_3[4];
    char cambio_4[4];
    char cambio_5[4];

    while (1){
        //PROBAR CONFIGURACION
        ADC0 -> PSSI |= (1<<2) | (1<<1);
        while ((ADC0 -> RIS & 6) == 0);
        entrada_adc=ADC0 -> SSFIFO1;
        ADC0 -> ISC =6;
        if (entrada_adc >= 2048){
            GPIOF -> DATA |= (1 << 1); 
        }
        else if (entrada_adc < 2048){
            GPIOF -> DATA &= ~(1 << 1); 
        }
        
        ADC_LECTURA(adc);
        lectura_0=adc[0];
        lectura_1=adc[1];
        lectura_2=adc[2];
        lectura_3=adc[3];
        lectura_4=adc[4];
        lectura_5=adc[5];

        // cambiar de entero a caracter
        itoa(lectura_0,cambio_0,10); //valor a cambiar, arreglo, base
        itoa(lectura_1,cambio_1,10);
        itoa(lectura_2,cambio_2,10);
        itoa(lectura_3,cambio_3,10);
        itoa(lectura_4,cambio_4,10);
        itoa(lectura_5,cambio_5,10);

        /*Interrupcion
        
        */

    }
    }

