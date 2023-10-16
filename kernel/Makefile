NAME	:= kernel.o
# i686-elf-gcc
CC		:= gcc -m32
CFLAGS	:= -std=gnu99 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		   -O2 -Wall -Wextra -I inc -MMD -MP
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	# I don't know what to do here
	touch $@

clean:
	$(RM) $(NAME) $(DEP) $(OBJ)

.PHONY: clean

-include $(DEP)
