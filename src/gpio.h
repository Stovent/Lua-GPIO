/** @file gpio.h
 * @brief Small library to control the GPIO of a Raspberry Pi.
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

/** @brief Init the library by mapping the GPIO memory.
 * @return true on success, false on error.
 */
bool gpio_init();

/** @brief Releases the mapped memory after usage. */
void gpio_exit();

/** @brief Inits the pin to input or output
 * @param pin The GPIO pin number.
 * @param output true to set as output, false as input.
 */
void gpio_init_pin(uint8_t pin, bool output);

/** @brief Sets the pin to high or low.
 * @param pin the GPIO pin number.
 * @param high true to set to high, false for low.
 */
void gpio_set_pin(uint8_t pin, bool high);

/** @brief Returns the state of the pin.
 * @param pin the GPIO pin number.
 * @return true when the pin is high, false when low.
 */
bool gpio_get_pin(uint8_t pin);

#endif // GPIO_H
