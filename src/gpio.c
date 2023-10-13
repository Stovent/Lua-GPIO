#include "gpio.h"

#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PERIPHERALS_BASE_ADDR (0x20200000)
#define MAP_SIZE (0xA0)

static uint32_t* gpio = NULL;
static int fdgpio = -1;

static const int fselShift[] = {
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27,
    0, 3, 6, 9,
};

static const int fsel[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5,
};

static const int set[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

static const int setShift[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
};

static const int clr[] = {
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
};

static const int* const clrShift = setShift;

static const int lvl[] = {
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
};

static const int* const lvlShift = setShift;

bool gpio_init()
{
    if((fdgpio = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
    {
        fprintf(stderr, "Could not open /dev/gpiomem: %s\n", strerror(errno));
        return false;
    }

    if((gpio = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fdgpio, PERIPHERALS_BASE_ADDR)) == MAP_FAILED)
    {
        fprintf(stderr, "Could not map gpio memory: %s\n", strerror(errno));
        return false;
    }

//    fputs("GPIO initialized\n", stdout);
    return true;
}

void gpio_exit()
{
    munmap(gpio, MAP_SIZE);
    close(fdgpio);
}

void gpio_init_pin(const uint8_t pin, const bool output)
{
    *(gpio + fsel[pin]) &= ~(1 << fselShift[pin]);
    *(gpio + fsel[pin]) |= (output << fselShift[pin]);

//    fprintf(stdout, "Pin %d set to %s\n", pin, output ? "output" : "input");
}

void gpio_set_pin(const uint8_t pin, const bool value)
{
    if(value)
        *(gpio + set[pin]) |=  (1 << setShift[pin]);
    else
        *(gpio + clr[pin]) |=  (1 << clrShift[pin]);

//    fprintf(stdout, "Set pin %d to value %d\n", pin, value);
}

bool gpio_get_pin(const uint8_t pin)
{
    const bool value = *(gpio + lvl[pin]) & (1 << lvlShift[pin]);

//    fprintf(stdout, "Get pin %d at value %d\n", pin, value);

    return value;
}
