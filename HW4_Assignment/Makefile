CC = gcc
CLINK = $(CC)
CFLAGS = -g -Wall -std=c99 -fPIC
LDFLAGS = -L. -llinked-list
LIBS = -lgrades -llinked-list

all: libgrades.so

libgrades.so: grades.o
	$(CC) -shared -o libgrades.so grades.o $(LDFLAGS)

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c grades.c
