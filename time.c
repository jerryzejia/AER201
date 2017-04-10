/*
 * File:   time.c
 * Author: jerryjia
 *
 * Created on March 24, 2017, 3:25 PM
 */

#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include "macros.h"
#include <stdio.h>
#include <xc.h>

extern const char timeSetter[7];
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 
extern unsigned char time[7];
extern char mode;



void get_time(unsigned char datime[7]) {
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC slave address + Write (0 LSB)
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    I2C_Master_Stop(); //Stop condition

    //Read Current Time
    I2C_Master_Start();
    I2C_Master_Write(0b11010001); //7 bit RTC address + Read (1 LSB)
    for(int i = 0; i < 6; i++){
        datime[i] = I2C_Master_Read(1);
    }
    datime[6] = I2C_Master_Read(0);
    I2C_Master_Stop();
}
/*
void initSortTimer(void){
    // 1 second timer to generate interrupts
    get_time(start_time);
 
    // Configure 16-bit timer with 1:256 prescaler
    T0CON = 0b00010111;
    // Load timer with value such that only 1 interrupt needs to occur to get to 1s
    // 32000000 CPU cycles per second
    // * 0.25 instructions per CPU cycle
    // * (1/256) timer ticks per instruction
    // = 31250 timer ticks per second
    // Now, we have a total of 65536 (2^16) bits in the timer. We need to overflow it.
    // Therefore, load the timer with 65526-31250 = 34286
    // d'34286 = 0b1000010111101110
    TMR0H = 0b10000101;
    TMR0L = 0b11101110;
    TMR0ON = 1;
}

void getSortTime(void){
    get_time(end_time);
    
    
    unsigned int start_sec = start_time[0] + start_time[1]*60 + start_time[2]*3600;
    unsigned int cur_sec = end_time[0] + end_time[1]*60 + end_time[2]*3600;
    unsigned int timeDiff = cur_sec - start_sec;
    unsigned int total_time = timeDiff;
    
    if(timeDiff >= 180){
        mode = 3;
        // STOP EXECUTION (switch to DoneSorting_state and make sure loop executing will see this)
    }
    
    int hour = timeDiff / 3600;
    int min = (timeDiff % 3600) / 60;
    int sec = (timeDiff % 3600) % 60;
    
    __lcd_home();
    printf("SORTING...");
    __lcd_newline();
    printf("TIME %d:%02d", min, sec);
}
*/