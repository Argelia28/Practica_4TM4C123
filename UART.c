#include "lib/include.h"

extern void Configurar_UART0(void)
{
    SYSCTL->RCGCUART  = (1<<0);   //Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<0);     //Paso 2 (RCGCGPIO) pag.340 Enable clock port A
    //(GPIOAFSEL) pag.671 Enable alternate function
    GPIOA->AFSEL = (1<<1) | (1<<0);
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOA->PCTL = (GPIOA->PCTL&0xFFFFFF00) | 0x00000011;// (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOA->DEN = (1<<0) | (1<<1);//PA1 PA0
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART0->CTL = (0<<9) | (0<<8) | (0<<0);
    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 25,000,000 / (16*57600) = 27.1267
    UARTFBRD[DIVFRAC] = integer(.1267 * 64 + 0.5)
    */
    UART0->IBRD = 27;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART0->FBRD = 7;
    //  UART Line Control (UARTLCRH) pag.916
    UART0->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART0->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART0->CTL = (1<<0) | (1<<8) | (1<<9);
}

extern void Configurar_UART4(void)
{
    SYSCTL->RCGCUART  = (1<<4);   //Pag.344 UART/modulo4 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<2);   //Puerto C pag.340 Enable clock
    GPIOC -> LOCK = 0x4C4F434B;
    GPIOC -> CR = 0x30; // Bit 4 y 5
    GPIOC->AFSEL = (1<<4) | (1<<5); // Pag. 672 pin 4 y 5 porque se usa C4 y C5
    //GPIOPCTL PC4->U4Rx PC5->U4Tx pag.689
    GPIOC->PCTL = (GPIOC->PCTL&0xFF00FFFF) | 0x00110000;// (1<<16) | (1<<20); *DUDA
    GPIOC->DEN = (1<<4) | (1<<5); //Pag. 683 PC4 PC5
    UART4->CTL = (0<<9) | (0<<8) | (0<<0); //Pag.918 DISABLE!!
    /* Pag.896
    BRD = 10,000,000 / (16*4800) = 130.20833
    UARTFBRD[DIVFRAC] = integer(.20833 * 64 + 0.5) = 13.833
    */
    UART4->IBRD = 130;
    UART4->FBRD = 13;
    UART4->LCRH = (0x3<<5)|(1<<4); // 0x3= 8 bits pag.916
    UART4->CC =(0<<0); // pag.939
    UART4->CTL = (1<<9) | (1<<8) | (1<<0); //Pag.918 ENABLE
}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART4->FR & (1<<4)) != 0 );
    v = UART4->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART4->FR & (1<<5)) != 0 );
    UART4->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern char * readString(char delimitador)
{

   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }

   return string;

}

//Experimento 2

//El envio es su nombre  (rave) 

// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 

