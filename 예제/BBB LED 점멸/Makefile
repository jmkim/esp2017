CC = armv8l-linux-gnueabihf-g++
LD = armv8l-linux-gnueabihf-g++
CCFLAGS = --std=c++14
LDFLAGS =

all: gpio_led bbb_led

gpio_led: gpio_led.o
	$(LD) -o $@ $^ $(LDFLAGS)

bbb_led: bbb_led.o
	$(LD) -o $@ $^ $(LDFLAGS)

gpio_led.o: gpio_led.cpp
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

bbb_led.o: bbb_led.cpp
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o *.d gpio_led bbb_led
