#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

bool gpio_init();
void gpio_exit();
void gpio_init_pin(const uint8_t pin, const bool output);
void gpio_set_pin(const uint8_t pin, const bool value);
bool gpio_get_pin(const uint8_t pin);

#endif // GPIO_H
