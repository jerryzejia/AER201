#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "pwm.h"
#include <stdio.h>
#include <xc.h>

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
  I NT1IE = 1;

  initLCD();
  I2C_Master_Init(10000);
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  I2C_Master_Stop();
  ei();
}
