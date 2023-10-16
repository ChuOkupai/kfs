NAME := boot.o

$(NAME): boot.asm
	nasm -felf32 $< -o $@

clean:
	$(RM) $(NAME)

.PHONY: clean
