CC = gcc
LD = gcc
CCFLAGS =
LDFLAGS =

all: demo

demo: main.o f1.o f2.o
	$(LD) -o $@ $^ $(LDFLAGS)

main.o: main.c f1.h
	$(CC) -c -o $@ $< $(CCFLAGS)

f1.o: f1.c f1.h f2.h
	$(CC) -c -o $@ $< $(CCFLAGS)

f2.o: f2.c f1.h f2.h
	$(CC) -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o demo
