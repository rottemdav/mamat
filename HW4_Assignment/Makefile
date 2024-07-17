CC=gcc
CLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.o
LDFLAGS=-L.

libgrades.so: grades.o 
	$(CLINK) -shared grades.o -o libgrades.so

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -fpic -c grades.c

clean:
	rm -rf *.o libgrades.so
