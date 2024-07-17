CC=gcc
CLINK=$(CC)
CFLAGS=-g -Wall -std=c99 -fPIC
OBJS=grades.o
LIBS=-lgrades -llinked-list
LDFLAGS=-L.

prog.exe: $(OBJS) libgrades.so liblinked-list.so
	$(CLINK) $(OBJS) -o prog.exe $(LDFLAGS) $(LIBS)

libgrades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c -o libgrades.o

libgrades.so: libgrades.o
	$(CLINK) -shared libgrades.o -o libgrades.so

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c -o grades.o

clean:
	rm -rf *.o *.exe *.so
