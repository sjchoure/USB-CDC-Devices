#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>  /* Calloc and Malloc function definitions */
#include <stdint.h>  /* uintx_t definitions */
#include <time.h>    /* Clock Definitions for Delay function */
#include <pthread.h>
#include "libusb.h"

#if MT==1
pthread_mutex_t serial_port_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
/**************************Serial Port Functions******************************/

int baudrate_to_index[] = {
	0,
	50,
	75,
	110,
	134,
	150,
	200,
	300,
	600,
	1200,
	1800,
	2400,
	4800,
	9600,
	19200,
	38400,
	57600,
	115200,
	230400,
	460800,
	500000,
	576000,
	921600,
	1000000,
	1152000,
	1500000,
	2000000,
};

const speed_t index_to_baudrate_const[] = {
	B0,
	B50,
	B75,
	B110,
	B134,
	B150,
	B200,
	B300,
	B600,
	B1200,
	B1800,
	B2400,
	B4800,
	B9600,
	B19200,
	B38400,
	B57600,
	B115200,
	B230400,
	B460800,
	B500000,
	B576000,
	B921600,
	B1000000,
	B1152000,
	B1500000,
	B2000000,
};

int open_serial_port(const char* port_name,int baudrate)
{
	int fd; //File descriptor for the port
	struct termios options;
	speed_t speed;

	fd = open(port_name, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		/*
		 * Could not open the port.
		 */
		perror("");
		fprintf(stderr, "open_serial_port: Unable to open %s\n", port_name);
		exit(EXIT_FAILURE);
	}
	else{
		fcntl(fd, F_SETFL, 0);
		/*
		 * Get the current options for the port...
		 */
		if (tcgetattr(fd, &options) != 0)
		{
    			perror("tcgetattr() error");
			exit(EXIT_FAILURE);
		}
		/*
		 * Set the baud rates
		 */
		for(int i = 0; i <= 27 ; i++ ) {
			if (i==27){
				fprintf(stderr,"Unknown Baudrate\n");
				exit(EXIT_FAILURE);
			}
			else if(baudrate == baudrateToIndex(i)){
				if (cfsetospeed(&options, indexToBaudrateConst(i)) != 0)
    					perror("cfsetospeed() error");
				if (cfsetispeed(&options, indexToBaudrateConst(i)) != 0)
					perror("cfsetispeed() error");
#if DP==1
				speed = cfgetispeed(&options);
				printf("The Input speed is %lu and baudrate is %d\n", (unsigned long) speed, baudrate);
				speed = cfgetospeed(&options);
				printf("The Output speed is %lu and baudrate is %d\n", (unsigned long) speed, baudrate);
#endif
				break;
			}
		}

		/*
		 * Enable the receiver, set local mode, set the parity to 8N1 and character size of 8 bits
		 */

		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;

		/*
		 * Set the new options for the port...
		 */

		if(tcsetattr(fd, TCSANOW, &options) < 0)
		{
			perror("tcsetattr() error");
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

int serial_write(int fd,const char* data){
#if MT == 1
	pthread_mutex_lock( &serial_port_mutex );
#endif
	int n = write(fd, data, strlen(data));
#if MT == 1
	pthread_mutex_unlock( &serial_port_mutex );
#endif
	if (n<0){
		return -1;
	}
	else
		return n;
}

int serial_read(int fd){
	char *buffer; /* Input Buffer */
	buffer = (char *)calloc(10,sizeof(char));
	char *bufptr;      /* Current char in buffer */
	int  nbytes;       /* Number of bytes read */
	/* read characters into our string buffer until we get a CR or NL */
	bufptr = buffer;
#if MT == 1
	pthread_mutex_lock( &serial_port_mutex);
#endif
	while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
	{
		bufptr += nbytes;
		if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
			break;
	}
#if MT == 1
	pthread_mutex_unlock( &serial_port_mutex);
#endif
	/* nul terminate the string and see if we got an OK response */
	*(bufptr-2) = '\0';
	//printf("serial_read(): %s\n",buffer);
	int num = (int)strtol(buffer,NULL,16); //Hexadecimal string to Hexadecimal Int
	free(buffer);
	return num;
}

void close_serial_port(int fd){
	close(fd);
}
//ADDONS
void printf_d(const char* p,uint8_t pin){
#if DP==1
	printf("*********************%s %d*********************\n",p,pin);
#endif
}
void printf_d_v(const char* p,uint8_t pin, uint8_t value){
#if DP==1
	printf("*********************%s %d %X*********************\n",p,pin,value);
#endif
}
void delay(int milliseconds)
{
	long pause;
	clock_t now,then;

	pause = milliseconds*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while( (now-then) < pause )
		now = clock();
}

/************************************PIN & PORT DEFINITIONS******************************/

const uint8_t port_to_mode[] = {
	NOT_A_PORT,
	DDRB,
	NOT_A_PORT,
	DDRD,
};

const uint8_t port_to_output[] = {
	NOT_A_PORT,
	PORTB,
	NOT_A_PORT,
	PORTD,
};

const uint8_t port_to_input[] = {
	NOT_A_PORT,
	PINB,
	NOT_A_PORT,
	PIND,
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PORT,
	PD,
	PD,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	PD,
	PD,
	NOT_A_PORT,
	PD,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	NOT_A_PORT,
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN,
	_BV(0),
	_BV(1),
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	_BV(4),
	_BV(5),
	NOT_A_PIN,
	_BV(6),
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	NOT_A_PIN,
};

/***************HELPER PIN MANIPULATION FUNCTIONS************************/

int get_reg_info(int fd,uint8_t reg){
	int status;
	char data[10];
	sprintf(data,"%02X ? ",reg);
#if DP==1
	printf("(Getting)Req:%s\t",data);
#endif
	if(serial_write(fd,data)==-1)
	{
		printf("serial_write() of %ld bytes failed! err(-1)\n",strlen(data));
		return -2;
	}
	status = serial_read(fd);
#if DP==1
	printf("Res:%02X\n",status);
#endif
	return status;
}

int set_reg_info(int fd,uint8_t reg,uint8_t value){
	int status;
	char data[10];
	sprintf(data,"%02X %02X = ",value, reg);
#if DP==1
	printf("(Setting)Req:%s\t",data);
#endif
	if(serial_write(fd,data)==-1)
	{
		printf("serial_write() of %ld bytes failed! err(-1)\n",strlen(data));
		return -2;
	}
	status = serial_read(fd);
#if DP==1
	printf("Res:%02X\n",value);
#endif
	return 0;
}

int init_board_port(int fd){
	int retry=0;
	printf_d("INITILISATION",0);
	printf("Initilising DDRB to 0xFF , PORTB to 0x00 , DDRD to 0x73 and PORTD to 0x00\n");
	while((get_reg_info(fd,DDRB)!=0xFF || get_reg_info(fd,PORTB)!=0x00 || get_reg_info(fd,DDRD)!=0x73 || get_reg_info(fd,PORTD)!=0x00) && retry <3)
	{
		set_reg_info(fd,DDRB,0xFF);
		set_reg_info(fd,PORTB,0x00);
		set_reg_info(fd,DDRD,0x73);
		set_reg_info(fd,PORTD,0x00);
		retry++;
	}
	if(retry >= 3)
	{	
		fprintf(stderr,"Initilisation failed!, kindly replug\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

/****************************PIN MANIPULATION FUNCTIONS*******************************/


void pinMode(int fd,uint8_t pin, uint8_t mode)
{	
	printf_d_v("PINMODE",pin,mode);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t ddreg,out;

	if(port == NOT_A_PORT || !(pin > 1 && pin < 20)) {
#if DP==1
		printf("The Pin %d is not an I/O pin, kindly check!\n",pin);
#endif
		return;
	}

	ddreg = portModeRegister(port);
	out = portOutputRegister(port);
#if DP==1
	printf("The bit = %X,port = %d,ddreg = %X,out_reg = %X\n",bit,port,ddreg,out);
#endif	
	//Getting Status of the IO registers
	uint8_t ddreg_value, out_value;
	ddreg_value = get_reg_info(fd,ddreg);
	out_value = get_reg_info(fd,out);

	if(mode == INPUT){
		ddreg_value &= ~(bit);
		set_reg_info(fd,ddreg,ddreg_value);

		out_value &= ~(bit);
		set_reg_info(fd,out,out_value);		
	}
	else if(mode == INPUT_PULLUP){
		ddreg_value &= ~(bit);
		set_reg_info(fd,ddreg,ddreg_value);

		out_value |= bit;
		set_reg_info(fd,out,out_value);
	}
	else {
		ddreg_value |= bit;
		set_reg_info(fd,ddreg,ddreg_value);
	}
	printf_d_v("PINMODE",pin,mode);
}

void digitalWrite(int fd,uint8_t pin, uint8_t val)
{
	printf_d_v("DIGITALWRITE",pin,val);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t out;

	if(port == NOT_A_PORT || !(pin > 1 && pin < 20)) {
#if DP==1
		printf("The Pin %d is not an I/O pin, kindly check!\n",pin);
#endif
		return;
	}

	out = portOutputRegister(port);
	//Getting status of the IO register
	uint8_t out_value;
	out_value = get_reg_info(fd,out);
	if(val == LOW) {
		out_value &= ~(bit);
		set_reg_info(fd,out,out_value);
	}
	else {
		out_value |= bit;
		set_reg_info(fd,out,out_value);
	}
	printf_d_v("DIGITALWRITE",pin,val);
}

int digitalRead(int fd,uint8_t pin)
{
	printf_d("DIGITALREAD",pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t in;

	if(port == NOT_A_PORT || !(pin > 1 && pin < 20)) {
#if DP==1
		printf("The Pin %d is not an I/O pin, kindly check!\n",pin);
#endif
		return LOW;
	}

	in = portInputRegister(port);
	//Getting the status of the IO Register
	uint8_t in_value = get_reg_info(fd,in);

	printf_d("DIGITALREAD",pin);
	if(in_value & bit) return HIGH;
	return LOW;
}

/***************************ADVANCE FEATURES**************************************/

uint8_t asciitohex(char a){
	char h[3];
	int num;
	sprintf(h,"%02X",a);
	num = (int)strtol(h,NULL,16); //Hexadecimal string to Hexadecimal Int
	return num;
}

uint8_t spidata(int fd,uint8_t MOSI, uint8_t MISO, uint8_t SCK, const char* p)
{
#if DP==1
	printf("\n\n");
	printf_d("SPIDATA LSB_BITFIRST",0);
	printf("\n\n");
#endif
	uint8_t receive = 0;
	int i = 0;
	while(p[i] !='\0')
	{
		uint8_t value = asciitohex(p[i]);
#if DP==1
		printf("ASCII %c to HEX %X\n",p[i],value);
#endif
		for(int j = 0;j < 8;j++){
#if DP==1
			printf("Bit %d:%X\n",j,bitRead(value,j));
#endif
			digitalWrite(fd,MOSI,bitRead(value,j));
			digitalWrite(fd,SCK,HIGH);
			//bitWrite(receive, j, digitalRead(fd,MISO)); // Capture MISO //FIXME
			digitalWrite(fd,SCK, LOW);
		}
		i++;
	}
#if DP==1
	printf("\n\n");
	printf_d("SPIDATA LSB_BITFIRST",0);
	printf("\n\n");
#endif
	return receive;
}


