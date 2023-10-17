NAME	:= kernel.o
CC		:= i686-elf-gcc
LINKER	:= ./link/linker.ld
CFLAGS	:= -std=gnu99 -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		   -O2 -Wall -Wextra -I inc -I /usr/include -MMD -MP
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -c -o crt0.o link/crt0.c
	$(CC) -o $(NAME) $(OBJ) -L/usr/lib32/ -lc

clean:
	$(RM) crt0.o crt0.d $(NAME) $(DEP) $(OBJ)

.PHONY: clean

-include $(DEP)
