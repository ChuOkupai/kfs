NAME		:= kfs.kernel
DOXYGEN_DIR	:= doc
LIBC_DIR	:= libc
IFLAGS		:= -I libc/inc -I kernel/inc -I /usr/include
LIBC		:= $(libc)/libk.a
KERNEL_DIR	:= kernel
KERNEL		:= $(KERNEL_DIR)/kernel.o
LINKER		:= $(KERNEL_DIR)/boot/linker.ld
CC			:= i686-elf-gcc
CFLAGS		:= -std=gnu11 -ffreestanding -nostdlib -O2 $(IFLAGS)

$(NAME): $(KERNEL) $(LIBC)
	$(CC) $(CFLAGS) -T $(LINKER) -o $@ $< -L $(LIBC_DIR) -lk

all: $(NAME)

clean:
	$(MAKE) -C $(LIBC_DIR) clean
	$(MAKE) -C $(KERNEL_DIR) clean
	$(RM) -r $(DOXYGEN_DIR) $(LIBC)

fclean: clean
	$(MAKE) -C $(LIBC_DIR) fclean
	$(MAKE) -C $(KERNEL_DIR) fclean
	$(RM) $(NAME)

doc:
	doxygen

docker:
	docker-compose up --build -d
	docker exec -it kfs make

re: fclean docker

run: docker
	qemu-system-i386 -kernel $(NAME)

$(LIBC):
	$(MAKE) -C $(LIBC_DIR)

$(KERNEL):
	$(MAKE) -C $(KERNEL_DIR)

.PHONY: all clean fclean doc docker re run
