#include <stdio.h>
#include "libusb.h"
int main(void){
	//Create a File Descriptor for the serial port
	int fd1 = open_serial_port("/dev/ttyACM0",115200);
	if(fd1 < 0) return -1;

	//Warning: Always initilise the cdc device before use, 
	//as it stores previous run values
	if(init_board_port(fd1) < 0) return -1;

	//Example of Configuring a pin as output. It can be OUTPUT, INPUT or INPUT_PULLUP
	pinMode(fd1,18,OUTPUT);

	//Example of a digital write for HIGH at a pin
	digitalWrite(fd1,18,LOW);

	//Example of a delay in millisecond
	delay(100);

	//Example of a digital write for LOW at a pin
	digitalWrite(fd1,18,HIGH);

	delay(100);

	//Example integer variable to store integer values
	int value;

	//Example of digital read at a pin
	value = digitalRead(fd1,18);

	printf("The digital level at pin %d is %d\n",18,value);

	//Alway close the respective opened file descriptor. C does not support garbage collection
	close_serial_port(fd1);
}
