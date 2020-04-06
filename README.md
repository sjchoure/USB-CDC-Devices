# USB-CDC-Devices
A Communication and Execution Code Driver for CDC Devices  
> Currently works perfectly with AT90S2313 Microcontroller

## What works?
 1. I/O Port Programming  
## Description
This repository consists of a driver program for working with the USB CDC Devices.  
The driver program is split up into two parts, the Crawler and Util respectively.
## Crawler
The crawler part contains the main function to make your logic work. It is used to call functions from the util part to handle various kinds of stuff. *It can be found inside the src/ directory.*
## Util
The util part is where the real magic happens. It consists of functions, which reside inside a library, libusb. The libusb is a static library. *It can be found inside the util/ directory.*   
There are three types of functions defined inside the library. These are as follows:
 1. Serial Communication functions
 2. Pin Manipulation functions
 3. Addon functions and Macros  
 
Each of these functions carries the importance of their own. Let's understand what each of these functions performs.
### Serial Communication functions
These are at the lowest level in the function hierarchy. These functions facilitate the use of serial communication protocol in our program. These functions are mainly based around the terminos library.  
Functions included are:
- extern int fd;
- int open_serial_port(const char*,int);
- int serial_write(int,const char*);
- int serial_read(int);
- void close_serial_port(int);

*Error message of -1 is returned from each of the function at the time of encounter. Expect for close_serial_port()*

### Pin Manipulation functions
These functions are bulit on the top of the **Serial Communication function**. The primary purpose of them are to change or read the logic level. The make of these functions are built around the most popular Arduino Source Code.  
Functions included are:
- int get_reg_info(int,uint8_t);
- void set_reg_info(int,uint8_t,uint8_t);
- void init_board_port(int);
- void pinMode(int,uint8_t,uint8_t);
- void digitalWrite(int,uint8_t,uint8_t);
- int digitalRead(int,uint8_t);  

*Error message of -2 is returned at the time of encounter.*  

*pinMode(), digitalWrite() and digitalRead() have inbuilt security feature. If the crawler program asks for a pin which is used for other usage apart from the I/O then the functions are not* ***EXECUTED.*** *They are returned with a warning message. Example includes use of pins such as Reset, XTAL1, XTAL2, VCC and GND*

### Addon Functions and Macros
These are in the used for extending the functionality of the library. These are really simple and basic functions to make life much easier.  
Functions amd Macros included are:  
- min(a,b)
- max(a,b)
- abs(x)
- round(x)     
- sq(x)
- radians(deg) 
- degrees(rad)
- void printf_d(const char*,uint8_t);
- void printf_d_v(const char*,uint8_t,uint8_t);
- void delay(int);  

## Compilation
To compile the source code just run with make command. It will automate all the neccessary task. Errors will be displayed at each stage if encountered. Inside the master directory:  

To build do,
> make program  

To remove the executable file do,  
> make clean
## Future Scope
- SPI Communication
- I2C Communication
- Other Internal Registers access
## References
For more details visit the following links:
 1. http://www.recursion.jp/prose/avrcdc/cdc-io.html For CDC Device Firmware
 2. https://www.cmrr.umn.edu/~strupp/serial.html For Serial Communication in POSIX
