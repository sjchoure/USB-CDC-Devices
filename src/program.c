#include <stdio.h>
#include "libusb.h"
#include <time.h>
int main(void){
	clock_t t;
	t = clock();
	//Create a File Descriptor for the serial port
	int fd1 = open_serial_port("/dev/ttyACM0",1000000);

	//Warning: Always initilise the cdc device before use, 
	//as it stores previous run values
	init_board_port(fd1);

	//Example of Configuring a pin as output. It can be OUTPUT, INPUT or INPUT_PULLUP
	pinMode(fd1,1,OUTPUT);

	//Example of a digital write for HIGH at a pin
	digitalWrite(fd1,12,LOW);

	//Example of a delay in millisecond
	delay(100);

	//Example of a digital write for LOW at a pin
	digitalWrite(fd1,12,HIGH);

	delay(100);

	//Example integer variable to store integer values
	int value;

	//Example of digital read at a pin
	value = digitalRead(fd1,12);

	printf("The digital level at pin %d is %d\n",12,value);

	//Alway close the respective opened file descriptor. C does not support garbage collection
	close_serial_port(fd1);

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	printf("fun() took %f seconds to execute \n", time_taken);

	return 0;
}
