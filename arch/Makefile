NAME	:= kernel.o
BFRLIMK	:= kernel-pre.o
LIBRARY	:= libk.a
CC		:= i686-elf-gcc
CFLAGS	:= -std=gnu11 -ffreestanding -nostdlib \
		   -O2 -Wall -Wextra -I inc -MMD -MP
LD		:= i686-elf-ld
SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP		:= $(SRC:%.c=%.d)
OBJ		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBRARY) $(BFRLIMK)
	$(LD) -r $^ -o $@

$(LIBRARY):
	$(MAKE) -C libc $(LIBRARY)
	mv libc/$(LIBRARY) .

$(BFRLIMK):
	$(MAKE) -C kernel
	mv kernel/kernel.o ./$(BFRLIMK)

clean:
	$(RM) $(LIBRARY) $(BFRLIMK) $(NAME)
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C kernel fclean
	$(MAKE) -C libc fclean

re: fclean all

.PHONY: clean all fclean re

-include $(DEP)
