
#include "lib/include.h"

extern void Configuracion_PWM(int freq, int freq_r, int ciclo)
{
    SYSCTL->RCGCPWM |= (1<<0); /*Enable modulo PWM0 pag 354*/
    SYSCTL->RCGCGPIO |= (1<<1); /*Enable Puerto B pag 340 pin 5*/
    SYSCTL->RCC &= ~(1<<20);  /*Enable o Disable Divisor  Pag 254*/
    GPIOB->AFSEL |= (1<<4)|(1<<5); /*Pin B4 y B5*/
    GPIOB->PCTL |= (GPIOB->PCTL&0xFF00FFFF) | 0x00440000; /* Configurar modo pwm Pag 689*/
    GPIOB->DEN |= (1<<4)|(1<<5); /* para decirle si es digital o no Pag 682*/
    
    PWM0->_1_CTL &= ~(1<<0);//Desactiva el generador 1
    PWM0->_1_CTL &= ~(1<<1); /*Modo countdown*/
    
    PWM0->_1_GENB = 0x0000008C; /*Registro de las acciones del pwm Pag 1285*/
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282*/
    
    PWM0->_1_LOAD = (freq_r/freq); /*cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)*/
   
    PWM0->_1_CMPA = (int)((1.0-(ciclo/100.0))*(freq_r/freq));

    PWM0->_1_CTL = (1<<1);// Se activa el generador 1

    PWM0->ENABLE = (1<<3) | (1<<2); /*habilitar los canales*/
}
