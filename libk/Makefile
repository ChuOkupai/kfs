NAME	= libk.a
SRC		:= $(wildcard src/*/*.c)
DEP		:= $(SRC:.c=.d)
OBJ		:= $(SRC:.c=.o)
CFLAGS	+= $(addprefix -I ,../kernel/inc inc private)

all: $(NAME)

clean:
	$(RM) $(DEP) $(NAME) $(OBJ)

re: clean all

.PHONY: all clean re

$(NAME): $(OBJ)
	ar rcs $@ $^

-include $(DEP)
