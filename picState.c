#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

extern char mode;
extern int flag;
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned char passed_time; 
extern unsigned char time[7];




void welcome() {
  __lcd_clear();
  __lcd_home();
  __delay_ms(200);
  printf("Welcome!");
  printf("            ");
  printf("2 Back to start menu");
  __lcd_newline();
  printf("1 Time");
  printf("              ");
  printf("A Sorting");
  while (mode == 0) {
  }
}

void debug() {
    __lcd_home();
    int i = canOn();
    printf("%d", i);
}
void sort() {

  int tap = 0;
  int tin = 0;
  int noLabel = 0;
  __lcd_clear();
  __delay_ms(100);
  printf("Sorting Started");
  __lcd_newline();
  printf("Press 1/2/A to stop");
  
  get_time(start_time);
  __lcd_home();
  // 1 = yes, 0 = no

  while (mode == 2) {
    if (PORTBbits.RB2 == 1) {
      // Everything here should be activated by a switch
      LATDbits.LATD0 = 1;
      __delay_ms(500);

      if (flag == 0) {
        __lcd_home();
        __lcd_newline();
        int can = sense_can();
        move_can(can);
        printf("%d", can);
        flag++;
      }
    } else {
      // move_can(sense_can());
      LATDbits.LATD0 = 0;
      __delay_ms(500);
      flag = 0;
    }
  }
}

void display_time() {
    
  __lcd_clear();
  __delay_ms(300);
  while (mode == 1) {
    I2C_Master_Start();
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
    for (unsigned char i = 0; i < 0x06; i++) {
      time[i] = I2C_Master_Read(1);
    }
    time[6] = I2C_Master_Read(0); // Final Read without ack
    I2C_Master_Stop();
    __lcd_home();
    printf("%02x/%02x/%02x", time[6], time[5],
           time[4]); // Print date in YY/MM/DD
    __lcd_newline();
    printf("%02x:%02x:%02x", time[2], time[1],
           time[0]);              // HH:MM:SS
                                  // Reset RTC memory pointer
    I2C_Master_Start();           // Start condition
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
    I2C_Master_Write(0x00);       // Set memory pointer to seconds
    I2C_Master_Stop();            // Stop condition
    // write new function!!
    __delay_ms(990);
    __lcd_home();
  }
  while (mode == 3) {
  }
}


void display_sorting_time() {
  __lcd_clear();
  __delay_ms(10);
  LATCbits.LATC1 = 0;
  int i = passed_time;
  printf("Time used: %d s", i);
  __lcd_newline();

  flag = 0;
  LATDbits.LATD0 = 0;
}
