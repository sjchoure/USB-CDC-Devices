/* this is the library header file for the libusb.c */
#include <stdint.h>
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define LOW 0x0
#define HIGH 0x1

/*********************USB Definitions********************************/
int open_serial_port(const char*,int);
int serial_write(int,const char*);
int serial_read(int);
void close_serial_port(int);

/*********************ADDONS****************************************/
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352
#define DP 1
// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define sq(x) ((x)*(x))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
void printf_d(const char*,uint8_t);
void printf_d_v(const char*,uint8_t,uint8_t);
void delay(int);

/*********************PIN Definitions*******************************/
#define NUM_DIGITAL_PIN 13
#define NOT_A_PORT 0
#define NOT_A_PIN 0
#define PB 2
#define PD 4
#define PORTB 0x38
#define DDRB 0x37
#define PINB 0x36
#define PORTD 0x32
#define DDRD 0x31
#define PIND 0x30
#define _BV(X) (1<<X)


//Macros to take the bit value of the pin
#define digitalPinToPort(P) (*(digital_pin_to_port + (P) - 1))
#define digitalPinToBitMask(P) (*(digital_pin_to_bit_mask + (P) - 1))
#define portOutputRegister(P) (*(port_to_output + (P) - 1))
#define portInputRegister(P) (*(port_to_input + (P) - 1))
#define portModeRegister(P) (*(port_to_mode + (P) - 1))

/****************************Modifying PIN*************************/
int get_reg_info(int,uint8_t);
void set_reg_info(int,uint8_t,uint8_t);
void init_board_port(int);
void pinMode(int,uint8_t,uint8_t);
void digitalWrite(int,uint8_t,uint8_t);
int digitalRead(int,uint8_t);


