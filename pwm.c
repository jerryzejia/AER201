/*
 * File:   pwm.c
 * Author: jerry
 *
 * Created on February 8, 2017, 2:48 AM
 */

#include <xc.h>
#include "configBits.h"

#include "I2C.h"

#define _XTAL_FREQ 32000000
#define TMR2PRESCALE 16

long freq;
unsigned int i = 0;

int PWM_Max_Duty()
{
    return(_XTAL_FREQ/(freq*TMR2PRESCALE));
}

void set_PWM_freq(long fre)
{
    PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
    freq = fre;
}

void set_PWM1_duty(unsigned int duty)
{
    if (duty<1024)
    {
        duty = ((float)duty/1023)*PWM_Max_Duty();
        CCP1X = duty & 2;
        CCP1Y = duty & 1;
        CCPR1L = duty >> 2;
    }
}

void PWM_Stop(){
    CCP1M3 = 0;
    CCP1M2 = 0;
    CCP1M1 = 0;
    CCP1M0 = 0;
}

void PWM1_Start()
{
    P1M1 = 0;
    P1M0 = 0;
    CCP1M3 = 1;
    CCP1M2 = 1;
    CCP1M1 = 0;
    CCP1M0 = 0;
    
    
    //timer prescaler if statements necessary
    
    T2CKPS0 = 1;
    T2CKPS1 = 1;
    
    TMR2ON = 1;
    TRISCbits.TRISC2 = 0;

    
}

