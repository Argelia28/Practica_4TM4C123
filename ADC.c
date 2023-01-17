
#include "lib/include.h"

extern void CONFIGURACION_ADC(void)
{
    SYSCTL -> RCGCADC = (1<<0);  //Pag 396 habilitar modulo 0
    SYSCTL -> RCGCADC = (1<<1); //Modulo 1
    SYSCTL -> RCGCGPIO = (1<<4) |(1<<5); //Pag 382
    //                PUERTO E  Y   F
    
    // led
    GPIOF -> DEN =  0xff;
    GPIOF -> AFSEL = 0x00;
    GPIOF -> DIR = 0xff;
    GPIOF -> DATA = (1<<1);

    GPIOE -> DIR = (0<<5) | (0<<4) | (0<<3) | (0<<2) | (0<<1) | (0<<0); //PE0 - PE5
    GPIOE -> AFSEL = 0x3F; // E0-E5
    GPIOE -> DEN = ~0x3F;
    //GPIOE -> PCTL = GPIOE->PCTL & (0xFF00FFFF);
    GPIOE -> AMSEL = 0x3F;
    
}
extern void CONFIGURACION_ADC_Seq(void){
    
    ADC0->ACTSS  = (0<<2) | (0<<1); //sec 2 y 1
    ADC0->EMUX  = (0xF<<8) | (0xF<<4); //trigger de sec 2 y 1
    
    ADC0->SSMUX1 = 0x210; // AN0, AN1, AN2
    ADC0->SSCTL1 = 0x666; // IE & END de los 3 canales

    ADC0->SSMUX2 = 0x983; // AN3, AN8, AN9
    ADC0->SSCTL2 = 0x666;
    // ADC0->PC = (0<<2)|(0<<1)|(1<<0);//250ksps

    ADC0->IM = (1<<2) | (1<<1);
    
    ADC0->ACTSS |= (1<<2) | (1<<1); //activar secuenciadores
    ADC0->ISC = 6;  //*DUDA

}


