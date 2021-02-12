#ifndef U8G2_HAL_RPI_PICO_H
#define U8G2_HAL_RPI_PICO_H

#include <cstdint>

extern "C" {
#include "u8g2.h"
}

/**
 * Byte communications callback for PIO Hardware on the Raspberry Pi Pico
 */
uint8_t cb_byte_pio_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/**
 * GPIO and Delay callback for Raspberry Pi
 */
uint8_t cb_gpio_delay_rpi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr);

#endif //U8G2DEMO_U8G2_HAL_RPI_H