# USB-CDC-Devices
A Communication and Execution Code Driver for CDC Devices   
<figure>
	<p align="center">
		<img src="https://github.com/saviourcode/USB-CDC-Devices/blob/master/image/block_diagram.png" alt='missing'>
		<figcaption>Fig: Block Diagram of Device</figcaption>
	</p> 
</figure>

> Currently works perfectly with AT90S2313 Microcontroller

## What works?
 1. I/O Port Programming 
 2. SPI MOSI as Master  
## Description
This repository consists of a driver program for working with the USB CDC Devices.  
The driver program is split up into two parts, the Crawler and Util respectively.
## Crawler
The crawler part contains the main function to make your logic work. It is used to call functions from the util part to handle various kinds of stuff. *It can be found inside the src/ directory.*
## Util
The util part is where the real magic happens. It consists of functions, which reside inside a library, libusb. The libusb is a static library. *It can be found inside the util/ directory.*   
There are four types of functions defined inside the library. These are as follows:
 1. Serial Communication functions
 2. Pin Manipulation functions  
		2.1 Pin & Ports Definintions  
		2.2 Helper Functions  
		2.3 Pin Initialise, Read and Write Functions
 3. Advance Features
 4. Addon functions and Macros  
 
Each of these functions carries the importance of their own. Let's understand what each of these functions performs.
### Serial Communication functions
These are at the lowest level in the function hierarchy. These functions facilitate the use of serial communication protocol in our program. These functions are mainly based around the terminos library.  
Functions included are:
- int(File Descriptor Return) open_serial_port(const char* (Port Name),int (Baudrate))
- int(Success(0) or Error(-1) Return) serial_write(int (File Descriptor),const char*(Data to write))
- int(Register Value or Error(-1) Return) serial_read(int (File Descriptor))
- void close_serial_port(int (File Descriptor))

*Error message of -1 is returned from each of the function at the time of encounter. Expect for close_serial_port()*

### Pin Manipulation functions
These functions are bulit on the top of the **Serial Communication function**. The primary purpose of them are to change or read the logic level. The make of these functions are built around the most popular Arduino Source Code.  
Functions included are:  
1. Pin and Port Definitions  
- port_to_mode[]
- port_to_output[]
- port_to_input[]
- digital_pin_to_port[]
- digital_pin_to_bit_mask[]  
2. Helper Functions  
- int(Status of the register or Error(-2) Return) ***get_reg_info***(int (File Descriptor),uint8_t(Register Address))
- int(Success (0) or Error(-2) Return) ***set_reg_info***(int (File Descriptor),uint8_t (Register Address) ,uint8_t (Value to Write))    
3. Pin Initialise, Read and Write Functions  
- int(Success(0) or Error(-3) Return) ***init_board_port***(int (File Descriptor))
- void ***pinMode***(int (File Descriptor),uint8_t(Pin Number),uint8_t(Mode: INPUT,INPUT_PULLUP,OUTPUT))
- void ***digitalWrite***(int (File Descriptor),uint8_t(Pin Number),uint8_t(State:HIGH or LOW))
- int(Value:1 or 0) ***digitalRead***(int (File Descriptor),uint8_t(Pin Number)  

*Error message of -2 is returned at the time of encounter.*  

*pinMode(), digitalWrite() and digitalRead() have inbuilt security feature. If the crawler program asks for a pin which is used for other usage apart from the I/O then the functions are not* ***EXECUTED.*** *They are returned with a warning message. Example includes use of pins such as Reset, XTAL1, XTAL2, VCC and GND*  

### Advance Features
BitBanged SPI Interface is supported by the devices. Currently only Master Out and Slave In communication is working. Work is still left for Master in Slave Out. Example of SPI can be found inside src/spi.c.  
Functions Included are:  
- uint8_t(Hex Value Return) ***asciitohex***(char (ASCII Character))
- uint8_t(MISO Received Data) ***spidata***(int (File Descriptor),uint8_t(MOSI Pin),uint8_t(MISO Pin),uint8_t(SCK Pin),const char*(Data to be sent))  

### Addon Functions and Macros
These are in the used for extending the functionality of the library. These are really simple and basic functions to make life much easier.  
Functions and Macros included are:  
- min(a,b)
- max(a,b)
- round(x)     
- sq(x)
- radians(deg) 
- degrees(rad)
- void printf_d(const char*,uint8_t)
- void printf_d_v(const char*,uint8_t,uint8_t)
- void delay(int)   
#### Mutlithreading Addon
To enable the Multithreading, make the #define MT 1 in util/libusb.h
To use threading, the library provides standard calls to the pthread.h library. It uses a MUTEX named as serial_port_mutex for making the serial_port accessible to either of the thread.

To get an idea about the threading see the example in src folder thread.c. It shows how to the threads can access each pin independent of what the other thread is doing.

## Compilation
*For custom made source code place them inside the src folder or else you need to make changes in the makefile.*  
To compile the source code just run with make command. It will automate all the neccessary task. Errors will be displayed at each stage if encountered. Inside the master directory:  

**To build a particular "file.c" inside the src folder do,**
> make Target=file

*Eg.* 
> make Target=program  
or  
> make Target=thread

**To run the executable do,**
> sudo ./file

*Eg.*
> sudo ./program  
or  
> sudo ./thread

**To remove the executable "file" do,**  
> make clean Target=file

*Eg.*
> make clean Target=program  
or  
> make clean Target=thread

To disable the Debugging Print Statements make #define DP 0 from 1 in util/libusb.h, this will make all logs to disable.

## Future Scope
- SPI Communication as MISO
- I2C Communication
- Other Internal Registers access
## References
For more details visit the following links:
 1. http://www.recursion.jp/prose/avrcdc/cdc-io.html For CDC Device Firmware
 2. https://www.cmrr.umn.edu/~strupp/serial.html For Serial Communication in POSIX
