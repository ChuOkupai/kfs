NAME	:= kernel.o
SRC_C	:= $(foreach pattern,* */*,$(wildcard src/$(pattern).c))
DEP		:= $(SRC:.c=.d)
SRC_ASM	:= $(foreach pattern,* */*,$(wildcard src/$(pattern).s))
OBJ		:= $(SRC_C:.c=.o) $(SRC_ASM:.s=.s.o)
CFLAGS	+= $(addprefix -I ,/usr/include ../libk/inc inc private)

all: $(NAME)

clean:
	$(RM) $(DEP) $(NAME) $(OBJ)

re: clean all

.PHONY: all clean re

$(NAME): $(OBJ)
	$(LD) -m elf_i386 -r $^ -o $@

%.s.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)
