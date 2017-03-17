/*
 * File:   main.c
 * Author: True Administrator
 *
 * Created on July 18, 2016, 12:11 PM
 */
#include "main.h"

const char timeSetter[7] = {
    0x00, // Seconds
    0x19, // Minutes
    0x15, // hour mode, set to 23:00
    0x04, // Wednesday
    0x25, // 25th
    0x01, // January
    0x17  // 2017
};
unsigned char mode = 0;
unsigned char start_time[7];
unsigned char end_time[7];
unsigned char passed_time;
unsigned char Count;
const char keys[] = "123A456B789C*0#D";

int en1 = 0;
int en2 = 0;

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

void interrupt keypressed(void) {
  if (INT1IF) {
    __lcd_newline();
    unsigned char keypress = (PORTB & 0xF0) >> 4;
    putch(keys[keypress]);
    if (mode == 2) { // get operation time
      get_time(end_time);
      passed_time =
          (end_time[1] - start_time[1]) * 60 + (end_time[0] - start_time[0]);
      mode = 3;

    } else if (keypress == 0x0) { // display time
      if (mode == 0) {
        mode = 1;
      }

    } else if (keypress == 0x3) { // sort
      if (mode == 0) {
        mode = 2;
      }
    }

    else if (keypress == 0x1) { // back
      mode = 0;

    } else if (keypress == 0x2) {
      mode = 99;
    }
  }
  INT1IF = 0; // Clear flag bit
}

void main(void) {
  int flag = 0; // Temporary Counter, remove after having microswitchers

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

  initLCD();
  I2C_Master_Init(10000);
  I2C_Master_Start();           // Start condition
  I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
  I2C_Master_Write(0x00);       // Set memory pointer to seconds
  I2C_Master_Stop();            // Stop condition
  passed_time = 0;
  unsigned char time[7];

  INT1IE = 1;
  mode = 0;
  ei(); // Enable all interrupts

  while (1) {
    if (mode == 0) {
      welcome();

    } else if (mode == 1) {
      display_time();
    }

    else if (mode == 2) {
      sort();
    }

    else if (mode == 3) {
      display_sorting_time();
    }

    else if (mode == 99) {
      debug();
    }
  }
  return;
}
