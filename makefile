SRC_Main = ./src/program.c
SRC_Lib = ./util/libusb.c
H_Lib = ./util/libusb.h
H_Lib_Loc = ./util
Target = program

program: program.o libusb.a
	$(info ***********************Building program.out***********************)
	gcc -o ${Target} program.o -L. -lusb

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

