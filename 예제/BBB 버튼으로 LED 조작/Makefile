CC = arm-linux-gnueabihf-g++
LD = arm-linux-gnueabihf-g++
CCFLAGS =
LDFLAGS = -static

all: gpio_led

gpio_led: gpio_led.o
	$(LD) -o $@ $^ $(LDFLAGS)

gpio_led.o: gpio_led.c
	$(CC) -MMD -c -o $@ $< $(CCFLAGS)

clean: 
	rm -f *.o *.d gpio_led
