NAME		:= chor.iso
ISO_DIR		:= iso
KERNEL_FILE	:= kfs.kernel
CFLAGS		+= $(addprefix -I ,/usr/include kernel/inc libk/inc)

all: run

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libk clean
	$(RM) -r doc $(ISO_DIR) $(NAME)

doc:
	doxygen

docker:
	docker-compose up --build -d
	docker exec -it kfs make $(NAME)

kernel:
	$(MAKE) -C $@ -j

libk:
	$(MAKE) -C $@ -j

re: clean docker

run: docker
	qemu-system-i386 -cdrom $(NAME)

.PHONY: all clean doc docker kernel libk re run

$(KERNEL_FILE): kernel libk
	$(CC) $(CFLAGS) -T kernel/conf/linker.ld -o $@ kernel/kernel.o -L libk -lk

$(NAME): $(KERNEL_FILE)
	mkdir -p $(ISO_DIR)/boot/grub
	mv $(KERNEL_FILE) $(ISO_DIR)/boot
	cp kernel/conf/grub.cfg $(ISO_DIR)/boot/grub
	grub-mkrescue -o $@ $(ISO_DIR)
