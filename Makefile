CC=gcc
INCLUDES=./include/
SOURCES=./source/site.c
BINARY=./test
PROG=./source/main.c

all:
	$(CC) -g -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) 

run:
	$(BINARY)


