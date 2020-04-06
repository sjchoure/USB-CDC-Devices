#include <stdio.h>
#include "libusb.h"
#define PIN 19
int main(void){
	open_serial_port("/dev/ttyACM0",19200);
	init_board_port();
	pinMode(PIN,OUTPUT);
	digitalWrite(PIN,HIGH);
	int value;
	value = digitalRead(PIN);
	printf("The digital level at pin 19 is %d\n",value);
	delay(1000);
	printf("The delay of 1 second\n");
	delay(500);
	printf("The delay of 0.5 second\n");
	delay(250);
	printf("The delay of 0.25 second\n");
	delay(100);
	printf("The delay of 0.1 second\n");
	delay(10);
	printf("The delay of 0.01 second\n");

	/*int fd = open_port("/dev/ttyACM0",9600);

	  serial_write(&fd,"FF 37 = "); //Make all portb as output
	  serial_read(&fd);

	  serial_write(&fd,"12 38 = "); //set 12 to portb
	  serial_read(&fd);

	  serial_write(&fd,"36 ? "); //what is the state on portb
	  serial_read(&fd);*/

	  //serial_write(&fd,"FF 37 = "); //set 00 to portb
	  //serial_read(&fd);

	  //serial_write(&fd,"37 ? "); //what is the state on portb
	  //serial_read(&fd);

	  close_serial_port(&fd);
}
