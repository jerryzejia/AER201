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


void shaker(){
    int i = 0;
    for (i = 0; i<200; i++){
        
        LATBbits.LATB2 = 1;
        LATCbits.LATC1 = 1;

        __delay_ms(8.5);
        
        LATCbits.LATC1 = 1;
        LATBbits.LATB2 = 0;

        __delay_ms(10);
    
        LATBbits.LATB2 = 0;
        LATCbits.LATC1 = 0;

        __delay_ms(1.5);
    }
}
/*
void blocker(){
    int i = 0;
    for (i = 0; i<10; i++){
        LATCbits.LATC1 = 1;
        __delay_ms(15);
        LATCbits.LATC1 = 0;
        __delay_ms(15);
    }
}*/