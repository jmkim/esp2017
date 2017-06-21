#include <stdio.h>
#include <unistd.h>

#define GPIO_VALUE_PATH(num) ("/sys/class/gpio/gpio" num "/value")
#define GPIO_DIRECTION_PATH(num) ("/sys/class/gpio/gpio" num "/direction")

#define GPIO_LED "30"
#define GPIO_BUTTON "31"

#define SLEEP_TIME_MICROSECONDS 100000

void
gpio_dir_in(FILE * fd)
{
    fputs("in", fd);
}

void
gpio_dir_out(FILE * fd)
{
    fputs("out", fd);
}

void
gpio_val_set(FILE * fd, int value)
{
    fprintf(fd, "%d", value);
}

int
gpio_val_get(FILE * fd)
{
    return fgetc(fd);
}

void
init(void)
{
    FILE * fd_led = fopen(GPIO_DIRECTION_PATH(GPIO_LED), "w");
    gpio_dir_out(fd_led);
    fclose(fd_led);

    FILE * fd_button = fopen(GPIO_DIRECTION_PATH(GPIO_BUTTON), "w");
    gpio_dir_in(fd_button);
    fclose(fd_button);
}

void
led_off(void)
{
    FILE * fd_led = fopen(GPIO_VALUE_PATH(GPIO_LED), "w");
    gpio_val_set(fd_led, 0);
    fclose(fd_led);
    usleep(SLEEP_TIME_MICROSECONDS);
}


void
led_on(void)
{
    FILE * fd_led = fopen(GPIO_VALUE_PATH(GPIO_LED), "w");
    gpio_val_set(fd_led, 1);
    fclose(fd_led);
    usleep(SLEEP_TIME_MICROSECONDS);
}

int
button(void)
{
    FILE * fd_button = fopen(GPIO_VALUE_PATH(GPIO_BUTTON), "r");
    int retval = gpio_val_get(fd_button);
    fclose(fd_button);
    return retval;
}

int
main(void)
{
    init();

    while(1)
    {
        led_off();
        while(button() == '1');

        led_on();
        while(button() == '0');
    }

    return 0;
}
