all:
	$(MAKE) -C boot
	$(MAKE) -C kernel

clean:
	$(MAKE) -C boot clean
	$(MAKE) -C kernel clean

.PHONY: all clean
