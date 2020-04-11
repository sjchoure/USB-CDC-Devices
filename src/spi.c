#include <pthread.h>
#include <stdio.h>
#include "libusb.h"
#include <time.h>
#include <unistd.h>

//Arduino PIN to AT90S2313 PIN

// 13 - SCk - 19
// 12 - MISO - 18
// 11 - MOSI - 17
// 10 - SS - 13

int main(void){
	//Create a File Descriptor for the serial port
	int fd1 = open_serial_port("/dev/ttyACM0",115200);

	//Warning: Always initilise the cdc device before use, 
	//as it stores previous run values
	init_board_port(fd1);

	pinMode(fd1,19,OUTPUT); //SCK
	pinMode(fd1,17,OUTPUT); //MOSI
	pinMode(fd1,13,OUTPUT); //SS

	//ALways keep the Slave disabled if no data
	digitalWrite(fd1,13,HIGH);

	//Make Slave Select Low to transfer Data
	digitalWrite(fd1,13,LOW);

	//Transfer Data using spidata() arguments are
	//file descriptor,MOSIpin, MISOpin, SCKpin,Data
	spidata(fd1,17,18,19,"Hello, World!\r");	

	//Make Slave Select High to disable it
	digitalWrite(fd1,13,HIGH);

	//Close the serial port
	close_serial_port(fd1);

	return 0;
}
