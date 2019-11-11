OUT		:= ./build
BIN     := $(OUT)/bin
OBJ     := $(OUT)/obj
INC     := ./inc
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
INCS	:= $(wildcard $(INC)/*.h)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS)) $(OBJ)/bootstrap.o
EXE     := $(BIN)/mykernel.elf

CC 		:= i686-elf-gcc
CFLAGS 	:= -std=c89 -Wall -Wextra -Wstrict-aliasing -pedantic -ffreestanding -g -I$(INC)
LDFLAGS := $(CFLAGS) -nostdlib -T $(SRC)/linker.ld

MKDIR	:= mkdir -p
RM		:= rm -rf
QEMU	:= qemu-system-i386 -kernel

.PHONY: all clean clobber run run_serial

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c $(INCS) | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/bootstrap.o: $(SRC)/bootstrap.s
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BIN) $(OBJ):
	$(MKDIR) $@

clean:
	$(RM) $(OUT)
	
clobber:
	$(RM) $(OBJ)
	
run: $(EXE)
	$(QEMU) $(EXE)

run_serial: $(EXE)
	$(QEMU) $(EXE) -chardev socket,id=tty0,host=127.0.0.1,port=5555,server,telnet -serial chardev:tty0 -nographic
