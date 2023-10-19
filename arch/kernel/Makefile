NAME	:= kernel.o
CC		:= i686-elf-gcc
CFLAGS	:= -std=gnu11 -ffreestanding -nostdlib \
		   -O2 -Wall -Wextra -I inc -MMD -MP
LD		:= i686-elf-ld
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	$(LD) -r $^ -o $@

clean:
	$(RM) $(NAME) $(DEP) $(OBJ)

.PHONY: clean

-include $(DEP)
