LIBRARY = libk.a
CC		:= i686-elf-gcc
IFLAGS	:= -I inc -I private -I ../kernel/inc -I /usr/include
CFLAGS 	:= -std=gnu11 -ffreestanding -nostdlib -O2 -Wall $(IFLAGS) -Wextra -Werror -MMD -MP

SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -rf $(LIBRARY)

re : fclean all

.PHONY: clean fclean all re
