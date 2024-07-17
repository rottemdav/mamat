CC = gcc
CLINK = $(CC)
CFLAGS = -g -Wall -std=c99 -fPIC
LDFLAGS = -L. -llinked-list
LIBS = -lgrades -llinked-list

all: libgrades.so

# Rule to create the shared library for grades
libgrades.so: grades.o
	$(CC) -shared -o libgrades.so grades.o $(LDFLAGS)

# Rule to create the object file for grades
grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c grades.c

# Clean up generated files
clean:
	rm -rf *.o libgrades.so

