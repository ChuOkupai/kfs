CC = i686-elf-gcc

all: docker boot kernel

boot: force
	docker exec -it kfs $(MAKE) -C boot CC=$(CC) 

kernel: force
	docker exec -it kfs $(MAKE) -C kernel CC=$(CC) 

docker:
	docker-compose -f docker up --build -d

clean:
	docker exec -it kfs $(MAKE) -C boot clean 
	docker exec -it kfs $(MAKE) -C kernel clean 

force:

.PHONY: all clean force
