#include "gpio.h"

#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>

#define PERIPHERALS_BASE_ADDR (0x20200000)

static volatile uint32_t* gpio = NULL;
static int fdgpio = -1;

enum GPIOPeripherals
{
    GPFSEL0 = 0x00,
    // GPFSEL1 = 0x04,
    // GPFSEL2 = 0x08,
    // GPFSEL3 = 0x0C,
    // GPFSEL4 = 0x10,
    // GPFSEL5 = 0x14,

    GPSET0 = 0x1C,
    // GPSET1 = 0x20,

    GPCLR0 = 0x28,
    // GPCLR1 = 0x2C,

    GPLEV0 = 0x34,
    // GPLEV1 = 0x38,

    GPEND = 0xA0, // End address
};

bool gpio_init()
{
    if((fdgpio = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
    {
        fprintf(stderr, "Could not open /dev/gpiomem: %s\n", strerror(errno));
        return false;
    }

    if((gpio = mmap(NULL, GPEND, PROT_READ | PROT_WRITE, MAP_SHARED, fdgpio, PERIPHERALS_BASE_ADDR)) == MAP_FAILED)
    {
        fprintf(stderr, "Could not map gpio memory: %s\n", strerror(errno));
        return false;
    }

    return true;
}

void gpio_exit()
{
    munmap((void*)gpio, GPEND); // Cast to avoid volatile discard warning.
    close(fdgpio);
}

#define FSEL_REG(pin) (pin / 10)
#define FSEL_BITS(pin) ((pin % 10) * 3)

void gpio_init_pin(const uint8_t pin, const bool output)
{
    const uint8_t addr = GPFSEL0 + FSEL_REG(pin);
    const uint8_t shift = FSEL_BITS(pin);

    uint32_t reg = gpio[addr];
    reg &= ~(7 << shift);
    reg |= (output << shift);
    gpio[addr] = reg;
}

#define SET_CLR_LVL_REG(pin) (pin >> 5)
#define SET_CLR_LVL_BIT(pin) (pin & 0x1Fu)

void gpio_set_pin(const uint8_t pin, const bool high)
{
    const uint8_t addr = high ? GPSET0 : GPCLR0;

    gpio[addr + SET_CLR_LVL_REG(pin)] = (1 << SET_CLR_LVL_BIT(pin));
}

bool gpio_get_pin(const uint8_t pin)
{
    return gpio[GPLEV0 + SET_CLR_LVL_REG(pin)] >> SET_CLR_LVL_BIT(pin) & 1;
}
