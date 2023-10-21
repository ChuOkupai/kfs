NAME	:= kernel.o
BOOT	:= boot.o
CC		:= i686-elf-gcc
IFLAGS	:= -I inc -I../libc/inc -Iinclude/kernel -I/usr/include/
CFLAGS	:= -std=gnu11 -nostdlib -O2 -Wall -Wextra $(IFLAGS) -MMD -MP
LD		:= i686-elf-ld
SRC_DIR	:= kernel/src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(BOOT)
	$(LD) -r $^ -o $@

$(BOOT): boot/boot.s
	i686-elf-as $< -o $@

clean:
	$(RM) -rf $(DEP) $(OBJ) $(BOOT)

fclean: clean
	$(RM) -rf $(NAME)

re : fclean all

.PHONY: clean fclean all re

-include $(DEP)