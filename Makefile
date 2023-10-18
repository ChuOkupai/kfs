NAME		:= kfs.bin
DOXYGEN_DIR	:= doc
BOOT_DIR	:= boot
BOOT		:= $(BOOT_DIR)/boot.o
KERNEL_DIR	:= kernel
KERNEL		:= $(KERNEL_DIR)/kernel.o
LINKER		:= $(KERNEL_DIR)/linker.ld
CC			:= i686-elf-gcc
CFLAGS		:= -std=gnu11 -ffreestanding -nostdlib -O2

$(NAME): $(BOOT) $(KERNEL)
	$(CC) $(CFLAGS) -T $(LINKER) -o $@ $^ -lgcc

all: $(NAME)

clean:
	$(MAKE) -C $(BOOT_DIR) clean
	$(MAKE) -C $(KERNEL_DIR) clean
	$(RM) $(NAME)
	$(RM) -r $(DOXYGEN_DIR)

doc:
	doxygen

docker:
	docker-compose up --build -d
	docker exec -it kfs make

$(BOOT):
	$(MAKE) -C $(BOOT_DIR)

$(KERNEL):
	$(MAKE) -C $(KERNEL_DIR)

.PHONY: all clean doc docker
