NAME	:= kernel.o
CC		:= i686-elf-gcc
CFLAGS	:= -std=gnu11 -nostdlib \
		   -O2 -Wall -Wextra -I inc -I../libc/inc -I/usr/include/ -MMD -MP
LD		:= i686-elf-ld
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) -r $^ -o $@

clean:
	$(RM) -rf $(DEP) $(OBJ)

fclean:
	$(RM) -rf $(NAME)

re : fclean all

.PHONY: clean fclean all re

-include $(DEP)
