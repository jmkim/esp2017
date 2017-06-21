CC = arm-linux-gnueabihf-g++
LD = arm-linux-gnueabihf-g++
CCFLAGS = --std=c++14
LDFLAGS =

all: gpio_led bbb_led

gpio_led: gpio_led.o
	$(LD) -o $@ $^ $(LDFLAGS)

bbb_led: bbb_led.o
	$(LD) -o $@ $^ $(LDFLAGS)

gpio_led.o: gpio_led.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

bbb_led.o: bbb_led.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o gpio_led bbb_led
