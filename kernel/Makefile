NAME		:= kernel.o
NAME_BONUS	:= kernel_bonus.o
BOOT		:= boot.o
AS			:= i686-elf-as
CC			:= i686-elf-gcc
IFLAGS		:= -I inc -I ../libc/inc -I inc/kernel -I/usr/include
CFLAGS		:= -std=gnu11 -nostdlib -O2 -Wall -Wextra -Werror -MMD -MP $(IFLAGS)
LD			:= i686-elf-ld
SRC_DIR		:= src
SRC			:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
DEP			:= $(SRC:%.c=%.d)
DEP_BONUS	:= $(SRC:%.c=%_bonus.d)
OBJ			:= $(DEP:%.d=%.o)
OBJ_BONUS	:= $(DEP_BONUS:%.d=%.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(BOOT)
	$(LD) -r $^ -o $@

$(NAME_BONUS): $(OBJ_BONUS) $(BOOT)
	$(LD) -r $^ -o $@

$(BOOT): boot/boot.s
	$(AS) $< -o $@

clean:
	$(RM) -rf $(DEP) $(DEP_BONUS) $(OBJ) $(OBJ_BONUS) $(BOOT)

fclean: clean
	$(RM) -rf $(NAME) $(NAME_BONUS)

re : fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %.c
	$(CC) $(CFLAGS) -DBONUS -c $< -o $@

.PHONY: all bonus clean fclean re

-include $(DEP)
