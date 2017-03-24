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
#include <stdio.h>
#include <xc.h>
extern const char timeSetter[7];

void set_time(void) {           // This program only has to be written once
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  for (char i = 0; i < 7; i++) {
    I2C_Master_Write(timeSetter[i]);
  }
  I2C_Master_Stop(); // Stop condition
  return;
}

void get_time(unsigned char datime[7]) {
  I2C_Master_Start();
  I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
  for (unsigned char i = 0; i < 0x06; i++) {
    datime[i] = I2C_Master_Read(1);
  }
  datime[6] = I2C_Master_Read(0); // Final Read without ack
  I2C_Master_Stop();
  // Reset RTC memory pointer
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  I2C_Master_Stop();            // Stop condition
}