NAME				:= chor.iso
NAME_BONUS			:= chor_bonus.iso
ISO_DIR				:= iso
KERNEL_FILE			:= kfs.kernel
KERNEL_FILE_BONUS	:= kfs_bonus.kernel
DOXYGEN_DIR			:= doc
LIBC_DIR			:= libc
IFLAGS				:= -I libc/inc -I kernel/inc -I /usr/include
LIBC				:= $(libc)/libk.a
KERNEL_DIR			:= kernel
KERNEL				:= $(KERNEL_DIR)/kernel.o
KERNEL_BONUS		:= $(KERNEL_DIR)/kernel_bonus.o
LINKER				:= $(KERNEL_DIR)/boot/linker.ld
CC					:= i686-elf-gcc
CFLAGS				:= -std=gnu11 -ffreestanding -nostdlib -O2 $(IFLAGS)

all: run

bonus: docker_bonus
	qemu-system-i386 -cdrom $(NAME_BONUS)

$(NAME): $(KERNEL_FILE)
	mkdir -p $(ISO_DIR)/boot/grub
	mv $< $(ISO_DIR)/boot
	cp kernel/boot/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)

$(NAME_BONUS): $(KERNEL_FILE_BONUS)
	mkdir -p $(ISO_DIR)/boot/grub
	mv $< $(ISO_DIR)/boot
	cp kernel/boot/grub_bonus.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

$(KERNEL_FILE): $(KERNEL) $(LIBC)
	$(CC) $(CFLAGS) -T $(LINKER) -o $@ $< -L $(LIBC_DIR) -lk

$(KERNEL_FILE_BONUS): $(KERNEL_BONUS) $(LIBC)
	$(CC) $(CFLAGS) -DBONUS -T $(LINKER) -o $@ $< -L $(LIBC_DIR) -lk

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

docker_bonus:
	docker-compose up --build -d
	docker exec -it kfs make $(NAME_BONUS)

re: fclean docker docker_bonus

run: docker
	qemu-system-i386 -cdrom $(NAME)

$(LIBC):
	$(MAKE) -C $(LIBC_DIR)

$(KERNEL):
	$(MAKE) -C $(KERNEL_DIR)

$(KERNEL_BONUS):
	$(MAKE) -C $(KERNEL_DIR) bonus

.PHONY: all bonus clean fclean doc docker docker_bonus re run
