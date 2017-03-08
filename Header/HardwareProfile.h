/*
 * This is the HardwareProfile for the PICMX250F128B
 * 
 */

#ifndef HARDWARE_PROFILE
#define HARDWARE_PROFILE


#define SYS_FREQ 40000000L

#define self_power     0

#define USE_USB_BUS_SENSE_IO
#define USB_BUS_SENSE  1 

void PIC32MX250_setup_pins(void);

#endif  //HARDWARE_PROFILE
