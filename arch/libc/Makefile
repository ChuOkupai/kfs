LIBRARY = libk.a
CC		:= i686-elf-gcc
CFLAGS 	:= -std=gnu11 -ffreestanding -nostdlib \
		   -O2 -Wall -Wextra -I inc -I/usr/include/ -I../inc -MMD -MP

SRC_DIR	:= src
SRC		:= $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ		:= $(SRC:%.c=%.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf $(OBJ) $(LIBRARY)

.PHONY: all clean