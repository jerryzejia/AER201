/*
 * File:   adc.c
 * Author: jerry
 *
 * Created on February 28, 2017, 10:05 PM
 */

#include<xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"




//Channel 0 = RA0
//Channel 1 = RA1
//Channel 2 = RA2
void readADC(char channel){
    ADCON0 = (ADCON0 & 0X3C)|((channel & 0x0F)<<2);
    ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_NOT_DONE){
    }

}
