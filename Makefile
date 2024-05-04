NAME		:= chor.iso
ISO_DIR		:= iso
KERNEL_FILE	:= kfs.elf
MODULES		:= kernel libk
CFLAGS		+= $(addprefix -I ,/usr/include kernel/inc libk/inc)

all: $(NAME) doc

clean:
	$(foreach module, $(MODULES), $(MAKE) -C $(module) clean;)
	$(RM) -r doc $(ISO_DIR) $(KERNEL_FILE) $(NAME)

doc: $(MODULES)
	doxygen

kernel:
	$(MAKE) -C kernel

libk:
	$(MAKE) -C libk

run:
	qemu-system-i386 -cdrom $(NAME)

.PHONY: all clean doc kernel libk run

$(KERNEL_FILE): $(MODULES)
	$(CC) $(CFLAGS) -T conf/linker.ld -o $@ kernel/kernel.o -L libk -lk

$(NAME): $(KERNEL_FILE)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_FILE) $(ISO_DIR)/boot
	cp conf/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)
