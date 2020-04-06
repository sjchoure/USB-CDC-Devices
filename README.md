# USB-CDC-Devices
A Commuincation and Execution Code Driver for CDC Devices

This repository consists of driver program for working with the USB CDC Devices.  
The driver program is split up into two parts, the Crawler and Util respectively.
## Crawler
The crawler part contains the main function to make your logic work. It is used to call functions from the util part to handle various stuffs.
## Util
The util part is where the real magic happens. It consists of functions, which resides inside a library, libusb. The libusb is a static library.  
There are three types of functions defined inside the library. These are as follows:

 1. **Serial Communication functions**
 2. **Pin Manipulation functions**
 3. **Addon functions and Macros**
 
Each of these functions carry importance of their own. Let's understand what each of these function perform.

### Serial Commuincation functions
These are in the lowest level in the function heiarchy. These functions facilitates the use of serial communication protocol in our program. These functions are mainly based around the terminos library.  
Functions included are:
- extern int fd;
- int open_serial_port(const char*,int);
- int serial_write(int*,const char*);
- int serial_read(int*);
- void close_serial_port(int*);

*Error message of -1 is returned from each of the function at the time of encounter. Expect for close_serial_port()*

### Pin Manipulation functions
These functions are bulit on the top of the **Serial Communication function**. The primary purpose of them are to change or read the logic level. The make of these functions are built around the most popular Arduino Source Code.  
Functions included are:
- int get_reg_info(uint8_t);
- void set_reg_info(uint8_t,uint8_t);
- void init_board_port();
- void pinMode(uint8_t,uint8_t);
- void digitalWrite(uint8_t,uint8_t);
- int digitalRead(uint8_t);  

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
