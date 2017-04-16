/*
 * File:   motor.c
 * Author: jerryjia
 *
 * Created on March 24, 2017, 3:55 PM
 */

#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

void blocker(){
    int i = 0; 
    for(i = 0; i < 100;i++){
        LATCbits.LATC0 = 1;
        __delay_ms(10);

        LATCbits.LATC0 = 0;
        __delay_ms(10);
    }
}

void shaker(){
    int i = 0;
    for (i = 0; i<100; i++){
        LATBbits.LATB2 = 1;
        __delay_ms(10);

        LATBbits.LATB2 = 0;
        __delay_ms(10);
    }
}

