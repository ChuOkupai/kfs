NAME		:= chor.iso
DOXYGEN_DIR	:= doc
ISO_DIR		:= iso
KERNEL_FILE	:= kfs.elf
MODULES		:= kernel/kernel.elf libk/libk.a
CFLAGS		+= $(addprefix -I ,kernel/inc libk/inc)
LDFLAGS		:= -T conf/linker.ld

all: $(NAME) $(DOXYGEN_DIR)

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(dir $(module)) clean;)
	$(RM) -r $(DOXYGEN_DIR) $(ISO_DIR) $(KERNEL_FILE) $(NAME)

run:
	qemu-system-i386 -cdrom $(NAME)

_force_check:
	@true

.PHONY: all clean run _force_check

$(DOXYGEN_DIR):
	doxygen

$(KERNEL_FILE): $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(MODULES): _force_check
	$(MAKE) -C $(dir $@) -j

$(NAME): $(KERNEL_FILE)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_FILE) $(ISO_DIR)/boot
	cp conf/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)
