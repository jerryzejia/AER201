/*
 * File:   initPic.c
 * Author: jerryjia
 *
 * Created on March 24, 2017, 3:11 PM
 */

#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

const char timeSetter[7] = {
    0x00, // Seconds
    0x19, // Minutes
    0x15, // hour mode, set to 23:00
    0x04, // Wednesday
    0x25, // 25th
    0x01, // January
    0x17  // 2017
};

unsigned char time[7];
unsigned char start_time[7];
unsigned char end_time[7];
unsigned char passed_time; 
int flag = 0;

void initPIC() {
  TRISA = 0b11110011; // All input mode
  TRISC = 0x11100110; // RC1 = PWM

  TRISC = 0x11100110;
  TRISD = 0x00; // All output mode
  TRISB = 0xFF; // All input mode
  LATB = 0x00;
  LATC = 0b00000000;
  ADCON0 = 0x00;
  ADCON1 = 0x0D;
  ADFM = 0;
  INT1IE = 1;

  initLCD();
  I2C_Master_Init(10000);
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  I2C_Master_Stop();
  ei();
}
