NAME	:= libc.a
CC		:= i686-elf-gcc
CFLAGS	:= -std=gnu99 -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs \
		   -O2 -Wall -Wextra -I inc -I /usr/include -MMD -MP
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(NAME) $(DEP) $(OBJ)

.PHONY: clean

-include $(DEP)