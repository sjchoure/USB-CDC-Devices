#include <stdio.h>
#include "libusb.h"
#define PIN 2
int main(void){
	//Create a File Descriptor for the serial port
	int fd1 = open_serial_port("/dev/ttyACM0",19200);

	//Warning: Always initilise the cdc device before use, 
	//as it stores previous run values
	init_board_port(fd1);

	//Example of Configuring a pin as output. It can be OUTPUT, INPUT or INPUT_PULLUP
	pinMode(fd1,PIN,OUTPUT);

	//Example of a digital write for HIGH at a pin
	digitalWrite(fd1,PIN,HIGH);

	//Example of a delay in microsecond
	delay(1000);

	//Example of a digital write for LOW at a pin
	digitalWrite(fd1,PIN,LOW);

	delay(1000);

	//Example integer variable to store integer values
	int value;

	//Example of digital read at a pin
	value = digitalRead(fd1,PIN);

	printf("The digital level at pin %d is %d\n",PIN,value);

	//Alway close the respective opened file descriptor. C does not support garabage collection
	close_serial_port(fd1);
}
