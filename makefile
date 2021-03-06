# Makefile Modified by Olimex Nov '12
# See old_README in the project folder for info on the
# earlier project.

NAME   = demo2294_blink_flash

PROJNAME = LPC-H2294
TARGET = main
OLIMEX_MSG = "OLIMEX OpenOCD projects (Eclipse Helios)"
MSG_BEGIN = "------ begin (proj:$(PROJNAME))------"
MSG_END   = ------  end  ------
LDSCRIPT = demo2294_blink_flash.cmd
EXEC   = main
SRCS=\
	main.c \
	Low_LVL/Init_ARM.c \
	Low_LVL/UART.c \
	Functions/Basic_blinkled.c \
	Functions/Deplacements.c \
	Functions/Asservissement_HL.c \
	Functions/Odometrie_HL.c \
	Low_LVL/pwm.c \
	Low_LVL/Asservissement_LL.c \
	Low_LVL/codeurs.c \
	Low_LVL/Interupt.c \
	Low_LVL/Timer.c \
	Low_LVL/Odometrie_LL.c \
	Functions/Routine_1ms.c \
	Functions/init.c \
	flags.c \
	Functions/Intel.c \
	Functions/SysTask.c \
	Functions/UsrTask.c \
	Low_LVL/can.c \
	Functions/can_HL.c \
	Functions/Msg_can.c \
	Functions/Debug_Bridge.c \
	Low_LVL/IO_AVR.c \
	Functions/TeamColor.c

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
OD		= arm-none-eabi-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  = -T$(LDSCRIPT) -Xlinker -Map=$(EXEC).map -nostartfiles -v 
CPFLAGS = -O binary
HEXFLAGS = -O ihex
ODFLAGS	= -x --syms
##################################################
##################################################
all: begin OBJ_DIR_CREATE build end

clean: begin clean_list end


begin:
	@echo 
	@echo $(OLIMEX_MSG)
	@echo $(MSG_BEGIN)

end:
	@echo
	@echo $(MSG_END)

########gene_crt########
crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s

########dir_funct########
OBJ_DIR_CREATE:
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi;
	@if [ ! -d $(OBJ_DIR)/Low_LVL ]; then mkdir $(OBJ_DIR)/Low_LVL; fi;
	@if [ ! -d $(OBJ_DIR)/Functions ]; then mkdir $(OBJ_DIR)/Functions; fi;
	
OBJ_DIR = .build
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

########build########
build: $(EXEC).out
	@ echo "...copying"
	$(CP) $(CPFLAGS) $(EXEC).out $(EXEC).bin
	$(OD) $(ODFLAGS) $(EXEC).out
	@echo "...building hex"
	$(CP) $(HEXFLAGS) $(EXEC).out $(EXEC).hex

########CLEAN########
clean_list:
	@ echo
	@ echo "Cleaning project..."
	@ echo
	-rm -f crt.lst $(EXEC).lst crt.o $(EXEC).o $(EXEC).out $(EXEC).hex $(EXEC).map $(EXEC).dmp $(EXEC).bin
	rm -rf $(OBJ_DIR) *~

########LD########
$(EXEC).out: $(OBJS) crt.o $(LDSCRIPT)
	@ echo "..linking"
	$(LD) $(LFLAGS) -o $(EXEC).out crt.o $(OBJS) -lm


########CC########
$(OBJ_DIR)/%.o: %.c Makefile
	@echo "compiling.. $<"
	@$(CC) -MD -MF $(OBJ_DIR)/$<.dep $(CFLAGS) -c $< -o $@

