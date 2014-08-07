# Available targets:
# make all /Do everything (main.elf and main.hex)
# make load /Program the device
# make clean /Clean
# make size /Get information about memory usage
# make filename.s /Generate assembler file from a C source
# make filename.o /Generate object file from a C source

#Source files
SRC_FILES=\
					main.c \
#					two.c \

#Object files
OBJ_FILES=$(SRC_FILES:.c=.o)

#Directories where to look for include files
INC_DIRS=\
					-I. \
					-Iincludes \

#Output file name
OUTPUT=main

#Programmer and port
PROG=usbasp
#PORT=usb

#Compiler related params
MCU=attiny85
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS= -mcall-prologues -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=$(MCU) -Wall -Wstrict-prototypes $(INC_DIRS)
#Optimization level
CFLAGS+=-Os
#Debug info
CFLAGS+=-gdwarf-2

#Generate hex file ready to upload
all: $(OUTPUT).elf
			$(OBJCOPY) -R .eeprom -O ihex $(OUTPUT).elf $(OUTPUT).hex
			@echo "--------------------------------"
			@echo " BUILD FINISHED "
			@echo "--------------------------------"

#Link output files
$(OUTPUT).elf: $(OBJ_FILES)
			$(CC)  $(CFLAGS)  $(OBJ_FILES)   -o $(OUTPUT).elf -Wl
#			$(CC)  $(CFLAGS)  $(OBJ_FILES)   -o $(OUTPUT).elf -Wl, -Map,$(OUTPUT).map

#Create object files
$(OBJ_FILES): %.o : %.c
			$(CC)   -c $(CFLAGS)  $<  -o  $@

#Create assembler file of a C source
%.s: %.c
			$(CC) -S $(CFLAGS)  $<  -o  $@
#Loads the program to the avr device
load:
			avrdude -p $(MCU) -c $(PROG) -e -U flash:w:$(OUTPUT).hex
#Get information about memory usage
size: $(OUTPUT).elf
			avr-size -C --mcu=$(MCU) $(OUTPUT).elf


#Cleans all generated files
clean:
		rm -f $(OBJ_FILES)
		rm -f $(OUTPUT).elf
		rm -f $(OUTPUT).hex
		rm -f $(OUTPUT).map