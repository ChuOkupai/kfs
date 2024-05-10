NAME		:= kernel.elf
SRC_ASM		:= $(shell find $(SRC_DIR) -type f -name '*.s')
SRC_C		:= $(shell find $(SRC_DIR) -type f -name '*.c')
DEP			:= $(SRC_C:%.c=$(BUILD_DIR)/%.d)
OBJ			:= $(SRC_ASM:%.s=$(BUILD_DIR)/%.o) $(DEP:.d=.o)
CFLAGS		+= $(addprefix -I ,../libk/inc inc)
LDFLAGS		:= -m elf_i386 -r

all: $(NAME)

clean:
	$(RM) -r $(BUILD_DIR) $(NAME)

.PHONY: all clean

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)
