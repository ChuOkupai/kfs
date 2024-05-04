NAME	:= kernel.o
SRC_ASM	:= $(foreach pattern,* */*,$(wildcard src/$(pattern).s))
SRC_C	:= $(foreach pattern,* */*,$(wildcard src/$(pattern).c))
DEP		:= $(SRC_C:.c=.d)
OBJ		:= $(SRC_ASM:.s=.o) $(SRC_C:.c=.o)
CFLAGS	+= $(addprefix -I ,/usr/include ../libk/inc inc private)

all: $(NAME)

clean:
	$(RM) $(DEP) $(NAME) $(OBJ)

.PHONY: all clean

$(NAME): $(OBJ)
	$(LD) -m elf_i386 -r $^ -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)
