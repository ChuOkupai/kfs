NAME	= libk.a
SRC		:= $(wildcard src/*/*.c)
DEP		:= $(SRC:.c=.d)
OBJ		:= $(SRC:.c=.o)
CFLAGS	+= $(addprefix -I ,../kernel/inc inc private)

all: $(NAME)

clean:
	$(RM) $(DEP) $(NAME) $(OBJ)

.PHONY: all clean

$(NAME): $(OBJ)
	ar rcs $@ $^

-include $(DEP)
