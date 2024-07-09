CC=gcc
CLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o stack.o student.o

prog.exe: $(OBJS)
	$(CLINK) $(OBJS) -o prog.exe

stack.o: stack.c stack.h common.h
	$(CC) $(CFLAGS) -c stack.c

student.o: student.c student.h common.h
	$(CC) $(CFLAGS) -c student.c

main.o: main.c common.h stack.h student.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o *.exe


