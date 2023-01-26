#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    SYSCTL->RCGCGPIO |=(1<<3); 
    GPIOD->LOCK= 0x4C4F434B;   // 2) unlock GPIO Port D
    GPIOD->CR = 0xF3;           // allow changes to PD0-1 4-7
    GPIOD->AMSEL = ~0xF3;        // 3) disable analog
    GPIOD->PCTL = ~0xF3;          // 4) PCTL GPIO on PD
    GPIOD->DIR = ~0xF3;          // 5) PD0, PD1, PD4, PD5, PD6, PD7 input=0
    GPIOD->AFSEL = ~0xF3;        // 6) disable alt funct on PD
    GPIOD->PUR = 0xF3;          // enable pull-up
    GPIOD->DEN = 0xF3;          // 7) enable digital I/O on PD

    GPIOD->IM = ~0xF3;         //pin d0-d1 y d4-d7 MASK
    GPIOD->IS = ~0xF3;          //POR FLANCO
    GPIOD->IBE = ~0xF3;          //configurado por evento, un flanco
    GPIOD->IEV = ~0xF3;         //por flanco si fuera 1 es por nivel
    GPIOD->IM = 0xF3;           //UNMASK

    /*GPIOD es la interrupcion 3
    n=integer(interrupt number/4)
      =integer(3/4)=0.75=0
    p=(interrupt number % 4)
      =(3%4)=3 -> pin 31-29
      4n+3 *duda*
      p=# interrupcion
    */
    NVIC->IP[0] = (NVIC->IP[0]&0x0FFFFFFF) | 0x30000000; //pin 29-31 y prioridad
    //NVIC->IP[0] = (NVIC->IP[0]&0xFFFFFFF0) | 0x00000003; //pin 3 y prioridad *duda*
    /*
    n=interrupt number/32
      =3/32=0
    b=interrupt number%32
      =3
    */
    NVIC->ISER[0]=(0UL<<3); //EN0 register and b is the pin
    
}

extern void Delay(void)
{
  GPIOD->ICR=0xF3; //Limpiar la interrupcion
}
