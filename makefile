Target = thread
SRC_Main = ./src/${Target}.c
SRC_Lib = ./util/libusb.c
H_Lib = ./util/libusb.h
H_Lib_Loc = ./util

program: libusb.a program.o
	$(info ***********************Building program.out***********************)
	gcc -o ${Target} ${Target}.o -L. -lusb -pthread

program.o: ${SRC_Main} ${H_Lib} 
	$(info ************************Building program.o************************)
	gcc -c ${SRC_Main} -I${H_Lib_Loc}

libusb.a: ${SRC_Lib} ${H_Lib}
	$(info ************************Building libusb.a*************************)
	gcc -c ${SRC_Lib} -I${H_Lib_Loc}
	ar -cvq libusb.a libusb.o
	ranlib libusb.a

clean:
	rm -f *.o *.a ${Target} 

