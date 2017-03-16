/*
 * File:   macros.h
 * Author: Administrator
 *
 * Created on August 17, 2016, 2:42 PM
 */

#ifndef MACROS_H
#define	MACROS_H

#define __delay_1s()                                                           \
  for (char i = 0; i < 100; i++) {                                             \
    __delay_ms(10);                                                            \
  }
#define __lcd_newline() lcdInst(0b11000000);
#define __lcd_clear() lcdInst(0x01);
#define __lcd_home() lcdInst(0b10000000);
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x20
#define LCD_LINE_3_ADDRESS lcdInst(11000000)
#define LCD_LINE_4_ADDRESS 0x60

#define TIN_LAB 1
#define TIN_NOLAB 2
#define POP_TAB 3
#define POP_NOTAB 4



#endif	/* MACROS_H */
