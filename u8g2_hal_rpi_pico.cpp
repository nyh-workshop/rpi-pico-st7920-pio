#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "u8g2_hal_rpi_pico.h"
#include "st7920.h"

const uint E_PIN = 15;
const uint RS_PIN = 14;
const uint RST_PIN = 22;
const uint D4_PIN = 18; 
ST7920 st7920(D4_PIN, E_PIN, RS_PIN, RST_PIN);

// U8G2's interface for now is only 8-bit parallel and SPI.
// These interface commands are being bypassed now as we manually display the framebuffer using the ST7920's fill screen.
uint8_t cb_byte_pio_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    uint8_t *_data;

    switch (msg) {
        case U8X8_MSG_BYTE_SET_DC: {
            break;
        }
        case U8X8_MSG_BYTE_SEND: {
            break;
        }
        case U8X8_MSG_BYTE_INIT: {            
            break;
        }
        case U8X8_MSG_BYTE_START_TRANSFER: {
            break;
        }
        case U8X8_MSG_BYTE_END_TRANSFER: {
            break;
        }
        default:
            return 0;
    }
    return 1;
}

uint8_t cb_gpio_delay_rpi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr) {
    switch (msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: {
            break;
        }
        case U8X8_MSG_DELAY_MILLI: {
            sleep_ms(arg_int);
            break;
        }
        case U8X8_MSG_DELAY_NANO: {
            break;
        }
        default: {
            return 0;
        }
    }
    return 1;
}
