
#include "lib/include.h"

extern void CONFIGURACION_ADC(void)
{
    SYSCTL -> RCGCADC = (1<<0);  //Pag 396 habilitar modulo 0
    SYSCTL -> RCGCADC = (1<<1); //Modulo 1
    SYSCTL -> RCGCGPIO = (1<<1) | (1<<3)| (1<<4) | (1<<5);
    //                PUERTO B      D        E       F
    
    // led para prueba.
    GPIOF -> DEN =  0xff;
    GPIOF -> AFSEL = 0x00;
    GPIOF -> DIR = 0xff;
    GPIOF -> DATA = (1<<1);

    // Canal 1=E2 3=E0 4=D3 5=D2 9=E4 11=B5
    GPIOE -> DIR = (0<<4) | (0<<2) | (0<<0); //PE4-PE2-PE0
    GPIOE -> AFSEL = (1<<4) | (1<<2) | (1<<0);//0x3F; E0-E5
    GPIOE -> DEN = ~(1<<4) | ~(1<<2) | ~(1<<0);//~0x3F;
    //GPIOE -> PCTL = GPIOE->PCTL & (0xFF00FFFF);
    GPIOE -> AMSEL = (1<<4) | (1<<2) | (1<<0);

    GPIOD -> DIR = (0<<3) | (0<<2); //PD3-PD2
    GPIOD -> AFSEL = (1<<3) | (1<<2);
    GPIOD -> DEN = ~(1<<3) | ~(1<<2);
    GPIOD -> AMSEL = (1<<3) | (1<<2);
    
    GPIOB -> DIR = (0<<5); //PB5
    GPIOB -> AFSEL = (1<<5);
    GPIOB -> DEN = ~(1<<5);
    GPIOB -> AMSEL = (1<<5);
}
extern void CONFIGURACION_ADC_Seq(void){
    ADC0->ACTSS  = (0<<1); //sec 1
    ADC0->EMUX  = (0xF<<4); //trigger de sec 1
    
    ADC0->SSMUX1 = 0x431; // AN1, AN3, AN4
    ADC0->SSCTL1 = 0x666; // IE & END de los 3 canales
    ADC0->PC = 0x7; // se configura a 1Msps
    ADC0->IM = (1<<1);

    ADC0->ACTSS |= (1<<1); //activar secuenciador
    ADC0->ISC = 2;  //*DUDA

    ADC1->ACTSS  = (0<<2); //sec 2
    ADC1->EMUX  = (0xF<<8); //trigger de sec 2

    ADC1->SSMUX2 = 0xB95; // AN5, AN9, AN11
    ADC1->SSCTL2 = 0x666;
    ADC1->PC = 0x7;// 1Msps
    ADC1->IM = (1<<2);
    
    ADC1->ACTSS |= (1<<2); //activar secuenciadores
    ADC1->ISC = 4;  //*DUDA.

}

extern void ADC_LECTURA(int lectura[6]){
    ADC0 -> PSSI = (1<<1); //Inicializa sec 1
    ADC1 -> PSSI = (1<<2); //Inicializa sec 2

    while ((ADC0 -> RIS & 0x2)|(ADC1 -> RIS & 0x4)){}; //la muestra completa la conversion
    lectura[0] = ADC0->SSFIFO1 & 0xFFF; //resultados
    lectura[1] = ADC0->SSFIFO1 & 0xFFF;
    lectura[2] = ADC0->SSFIFO1 & 0xFFF;
    lectura[3] = ADC1->SSFIFO2 & 0xFFF;
    lectura[4] = ADC1->SSFIFO2 & 0xFFF;
    lectura[5] = ADC1->SSFIFO2 & 0xFFF;

    ADC0->ISC = 0x2;
    ADC1->ISC = 0x4;
}


