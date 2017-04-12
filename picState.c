#include "I2C.h"
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "pwm.h"
#include "function.h"
#include <stdio.h>
#include <xc.h>

char mode;
extern unsigned char start_time[7];
extern unsigned char end_time[7];
extern unsigned int passed_time; 
extern unsigned char time[7];

int displayFlag = 0; 
int int_end_time[7];
int int_start_time[7];

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
  LATDbits.LATD0 = 0;
  LATCbits.LATC1 = 0;

  //main_servo_control(NEUTRAL);
  //side_servo_control(NEUTRAL);

  while (mode == 0) {
  }
}

void debug() {
<<<<<<< HEAD
    /*__lcd_home();
    get_time(start_time);
    printf("%02x/%02x/%02x", start_time[6], start_time[5],
           start_time[4]); // Print date in YY/MM/DD
    __lcd_newline();
    printf("%02x:%02x:%02x", start_time[2], start_time[1],
           start_time[0]);
=======
   //side_servo_control(NEUTRAL);
    //main_servo_control(NEUTRAL);
    //LATDbits.LATD0 = 1;
    //int i = sense_can();
    //printf("%d", i);
    /*int i = 0; 
    while(i < 50){
        __lcd_home();
        //int i = readLightSensor();
        readADC(5);

        printf("%x%x", ADRESH,ADRESL);
        __delay_ms(5);
        i++;
    }
    */ 
    
    int H_max = 0;
    int i = 0;
    while(1){
        __lcd_home();
        //int i = readLightSensor();
        readADC(0);
        printf("%x%x", ADRESH, ADRESL);

        /*if (ADRESH > H_max) {
            H_max = ADRESH;
        }
        printf("%x", ADRESH);
        __delay_ms(5);
        i++;
    }
    
    if(H_max >= 0x50){
       __lcd_home();
       printf("HI HI %x", H_max);
       __delay_ms(500);
    }
    else{
       __lcd_home();
       printf("LO LO %x",H_max);
       __delay_ms(500);

  */
>>>>>>> parent of ff33206... 。
    }
     */
    get_time(end_time);
    printf("%02x/%02x/%02x", end_time[6], end_time[5],
           end_time[4]); // Print date in YY/MM/DD
    __lcd_newline();
    printf("%02x:%02x:%02x", end_time[2], end_time[1],
           end_time[0]);
    
<<<<<<< HEAD
}
=======
    
    //gate();

}

>>>>>>> parent of ff33206... 。
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
    if (readLightSensor() == 1) {
      // Everything here should be activated by a switch
      LATDbits.LATD0 = 1;
<<<<<<< HEAD
=======
      main_servo_control(NEUTRAL);
      __delay_ms(1000);
     
>>>>>>> parent of ff33206... 。
        __lcd_home();
        __lcd_newline();
        int can = sense_can();
        LATDbits.LATD0 = 0;
        move_can(can);
<<<<<<< HEAD

        printf("%d", can);
=======
        printf("%d", can);
        flag++;
      
>>>>>>> parent of ff33206... 。
    } else {
      // move_can(sense_can());
      shaker();
      main_servo_control(NEUTRAL);
      LATDbits.LATD0 = 0;
      __delay_ms(500);      
      gate();
<<<<<<< HEAD
=======
      
      flag = 0;
>>>>>>> parent of ff33206... 。
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
}

void display_sorting_time() {
    int int_end_time[7];
    int int_start_time[7];
    __lcd_clear();

    get_time(end_time);
    for(int i = 0; i < 7; i++){
        int_end_time[i] = __bcd_to_num(end_time[i]);
    }
    for(int i = 0; i < 7; i++){
        int_start_time[i] = __bcd_to_num(start_time[i]);
    }
    if(displayFlag == 0){
        passed_time = (int_end_time[1] - int_start_time[1]) * 60 + (int_end_time[0] - int_start_time[0]);
        displayFlag++;
    }

  LATCbits.LATC1 = 0;
  printf("Time used: %d s", passed_time);
  __delay_ms(500);
  LATDbits.LATD0 = 0;
}
