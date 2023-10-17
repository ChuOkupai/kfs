CC			= i686-elf-gcc
DOXYGEN_DIR	:= doc/doxygen

all: docker boot kernel

boot: force
	docker exec -it kfs $(MAKE) -C boot CC=$(CC)

doc:
	mkdir -p $(DOXYGEN_DIR)
	doxygen

kernel: force
	docker exec -it kfs $(MAKE) -C kernel CC=$(CC) 

docker:
	docker-compose -f docker up --build -d

clean:
	docker exec -it kfs $(MAKE) -C boot clean 
	docker exec -it kfs $(MAKE) -C kernel clean 
	$(RM) -r $(DOXYGEN_DIR)

force:

.PHONY: all clean force
