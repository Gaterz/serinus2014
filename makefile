# Makefile Modified by Olimex Nov '12
# See old_README in the project folder for info on the
# earlier project.

NAME   = demo2294_blink_flash

PROJNAME = LPC-H2294
TARGET = main
OLIMEX_MSG = "OLIMEX OpenOCD projects (Eclipse Helios)"
MSG_BEGIN = "------ begin (proj:$(PROJNAME))------"
MSG_END   = ------  end  ------

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
OD		= arm-none-eabi-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  =  -Map main.map -Tdemo2294_blink_flash.cmd
CPFLAGS = -O binary
HEXFLAGS = -O ihex
ODFLAGS	= -x --syms

all: begin build end

clean: begin clean_list end

clean_list:
	@ echo
	@ echo "Cleaning project..."
	@ echo
	-rm -f crt.lst main.lst crt.o main.o main.out main.hex main.map main.dmp main.bin

build: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out
	@echo "...building hex"
	$(CP) $(HEXFLAGS) main.out main.hex

main.out: testmulti.o crt.o main.o demo2294_blink_flash.cmd 
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.out  crt.o main.o testmulti.o

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s

main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	
testmulti.o: testmulti.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) testmulti.c

begin:
	@echo 
	@echo $(OLIMEX_MSG)
	@echo $(MSG_BEGIN)

end:
	@echo
	@echo $(MSG_END)
