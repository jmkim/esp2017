CC = gcc
LD = gcc
ODIR = .obj
CCFLAGS =
LDFLAGS =

all: demo

demo: main.o f1.o f2.o
	$(LD) -o $@ $^ $(LDFLAGS)

main.o: main.c f1.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

f1.o: f1.c f1.h f2.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

f2.o: f2.c f1.h f2.h
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o *.d demo
