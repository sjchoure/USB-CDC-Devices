#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "libusb.h"

void *functionC1();
void *functionC2();

//Make the serial port file descriptor as global 
//as it will make it visible to all other processes.
int fd1;

int main()
{
	fd1 = open_serial_port("/dev/ttyACM0",1000000);

	//Device initilisation
	init_board_port(fd1)

	pinMode(fd1,19,OUTPUT);
	pinMode(fd1,18,OUTPUT);

	//Variables to check if the thread creation succeeded or not.
	int rc1, rc2;

	//Threads
	pthread_t thread1,thread2;

	/* Create independent threads each of which will execute functionC1 and functionC2 respectively */

	if( (rc1=pthread_create( &thread1, NULL, &functionC1, NULL)) )
	{
		printf("Thread creation failed: %d\n", rc1);
	}

	if( (rc2=pthread_create( &thread2, NULL, &functionC2, NULL)) )
	{
		printf("Thread creation failed: %d\n", rc2);
	}

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	close_serial_port(fd1);

	exit(0);
}

void *functionC1()
{
	while(1){
		digitalWrite(fd1,19,HIGH);
		delay(100);
		digitalWrite(fd1,19,LOW);
		delay(100);
	}
}

void *functionC2()
{
	while(1){
		digitalWrite(fd1,18,HIGH);
		delay(1000);
		digitalWrite(fd1,18,LOW);
		delay(1000);
	}
}

