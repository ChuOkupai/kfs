FROM debian:buster

RUN apt update && apt install -y \
	build-essential \
	doxygen \
	gcc-multilib \
	graphviz \
	grub-pc-bin \
	xorriso

WORKDIR /kfs

CMD ["make"]
