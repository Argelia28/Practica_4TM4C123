#include "lib/include.h"
#include <stdio.h>
uint32_t adc[10];

int main(void)
{
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj 50MHZ
    Configurar_GPIO();
    Configurar_UART0();
    //Configurar_SSI2();
    CONFIGURACION_ADC();
    CONFIGURACION_ADC_Seq();
    
    unsigned int entrada_adc;
    while (1){
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
    }
    }

