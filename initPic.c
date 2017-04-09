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
  TRISA = 0b11100111; 
  TRISC = 0x11100110; // RC1 = PWM

  TRISC = 0x11100100;
  TRISD = 0x00; // All output mode
  TRISB = 0b11111011; // All input mode
  TRISE = 0x00;
  
  //Set all output to low
  LATA = 0x00; // output low
  LATB = 0x00; // output low
  LATC = 0x00; // output low
  LATD = 0x00; // output low
  LATE = 0x00; // output low
  
  ADCON0 = 0x00;
  ADCON1 = 0x0C;
  
// Disable A/D conversion interrupts (important for readADC())
  ADCON2 = 0b00110001; // Left  justify A/D result, 16TAD, FOSC/8 clock
  INT1IE = 1;

  initLCD();
  //initSortTimer();
  I2C_Master_Init(10000);
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  I2C_Master_Stop();
  main_servo_control(NEUTRAL);
  side_servo_control(NEUTRAL);
  
  
  ei();
  /*
  TMR0IE = 1; // Enable Timer0 interrupts
  PEIE = 1; // Set peripheral interrupt enable bit (YOU MUST DO THIS IF YOU
              // DIDN'T SET INTERRUPT PRIORITIES (i.e. if IPEN=0)

  T0CON = 0b00010111;
  TMR0H = 0b10000101;
  TMR0L = 0b11101110;
  T0CON = T0CON | 0b10000000;
  */
  
}
