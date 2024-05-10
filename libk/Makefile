NAME		= libk.a
SRC			:= $(shell find $(SRC_DIR) -type f -name '*.c')
DEP			:= $(SRC:%.c=$(BUILD_DIR)/%.d)
OBJ			:= $(DEP:.d=.o)
CFLAGS		+= $(addprefix -I ,../kernel/inc inc private)

all: $(NAME)

clean:
	$(RM) -r $(BUILD_DIR) $(NAME)

.PHONY: all clean

$(NAME): $(OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)
