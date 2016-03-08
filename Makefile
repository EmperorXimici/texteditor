# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS= -g -c -Wall -O0
LDLIBS=
PNAME=cEdit
OBJECTS=core.o main.o

# These variables will hold the diffrent compile modes
RELEASE= -c -O3
DEBUG= -g -c -Wall -O0

all: build

build: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) -o $(PNAME)

core.o: core.c
	$(CC) $(CFLAGS) core.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

run: build
	./$(PNAME)

rebuild: clean build

clean:
	rm -rf *o $(PNAME)
	echo 'clean done..'
