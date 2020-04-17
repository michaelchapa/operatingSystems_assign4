# Rules for building .c version
all: assign4

assign4: assign4.c
	gcc -g -o assign4 assign4.c

