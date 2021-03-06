/*
 * File:   countCan.c
 * Author: jerryjia
 *
 * Created on March 27, 2017, 8:12 PM
 */

#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>
int pop_can_tap = 0;
int pop_can_no_tap = 0;
int soup_can_label = 0;
int soup_can_no_label = 0; 
int total_count = 0; 

/*                                                                         
 * TIN_LAB 1
 * TIN_NOLAB 2
 * POP_TAB 3
 * POP_NOTAB 4
 */
void count(int canType) {
    if(canType == TIN_LAB){
        soup_can_label++;
    }
    else if(canType == TIN_NOLAB){
        soup_can_no_label++;
    }
    else if(canType == POP_TAB){
        pop_can_tap++;
    }
    else if(canType == POP_NOTAB){
        pop_can_no_tap++;
    }
}

int ensureTotalCan(int total_count){
    total_count = soup_can_label + soup_can_no_label + pop_can_tap +
            pop_can_no_tap; 
    if(total_count > 12){
        return 1; 
    }
}