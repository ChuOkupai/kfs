NAME		:= chor.iso
ISO_DIR		:= iso
KERNEL_FILE	:= kfs.kernel
DOXYGEN_DIR	:= doc
LIBC_DIR	:= libc
IFLAGS		:= -I libc/inc -I kernel/inc -I /usr/include
LIBC		:= $(libc)/libk.a
KERNEL_DIR	:= kernel
KERNEL		:= $(KERNEL_DIR)/kernel.o
LINKER		:= $(KERNEL_DIR)/boot/linker.ld
CC			:= i686-elf-gcc
CFLAGS		:= -std=gnu11 -ffreestanding -nostdlib -O2 $(IFLAGS)

all: run

$(NAME): $(KERNEL_FILE)
	mkdir -p $(ISO_DIR)/boot/grub
	mv $(KERNEL_FILE) $(ISO_DIR)/boot
	cp kernel/boot/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)

$(KERNEL_FILE): $(KERNEL) $(LIBC)
	$(CC) $(CFLAGS) -T $(LINKER) -o $@ $< -L $(LIBC_DIR) -lk

clean:
	$(MAKE) -C $(LIBC_DIR) clean
	$(MAKE) -C $(KERNEL_DIR) clean
	$(RM) -r $(DOXYGEN_DIR) $(LIBC)
	$(RM) -r $(ISO_DIR)
	$(RM) $(KERNEL_FILE)

fclean: clean
	$(MAKE) -C $(LIBC_DIR) fclean
	$(MAKE) -C $(KERNEL_DIR) fclean
	$(RM) $(NAME)

doc:
	doxygen

docker:
	docker-compose up --build -d
	docker exec -it kfs make $(NAME)

re: fclean docker

run: docker
	qemu-system-i386 -cdrom $(NAME)

$(LIBC):
	$(MAKE) -C $(LIBC_DIR)

$(KERNEL):
	$(MAKE) -C $(KERNEL_DIR)

.PHONY: all clean fclean doc docker re run
