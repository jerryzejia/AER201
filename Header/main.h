
void set_time(void);
void get_time(unsigned char *);
void startMotor(int dir);
void stopMotor(void);
void readADC(char channel);
void motorMove(unsigned char *);
void move_can(int can_type);
int sense_can();
void delay_ms(unsigned int milliseconds);
void servo_control();
