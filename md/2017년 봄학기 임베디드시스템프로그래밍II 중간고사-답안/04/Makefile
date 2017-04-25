PROG = calc
IDIR = include

CC = gcc
CCFLAGS = -I$(IDIR)

LD = gcc
LDFLAGS =

all: $(PROG)

$(PROG): stack.o arithmetic.o calc.o
	$(LD) -o $@ $^ $(LDFLAGS)

stack.o: stack.c $(IDIR)/stack.h
	$(CC) -c -o $@ $< $(CCFLAGS)

arithmetic.o: arithmetic.c $(IDIR)/arithmetic.h
	$(CC) -c -o $@ $< $(CCFLAGS)

calc.o: calc.c $(IDIR)/stack.h $(IDIR)/arithmetic.h
	$(CC) -c -o $@ $< $(CCFLAGS)

install:
	cp $(PROG) ~/bin/

clean:
	rm -f *.o $(PROG)
