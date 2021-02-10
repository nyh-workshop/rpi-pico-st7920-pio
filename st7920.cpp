#include <stdio.h>
#include "st7920.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"

ST7920::ST7920(uint D4_PIN, uint E_PIN, uint RS_PIN, uint RST_PIN) {
    D4_PIN_ = D4_PIN;
    E_PIN_ = E_PIN;
    RS_PIN_ = RS_PIN;
    RST_PIN_ = RST_PIN;
}

void ST7920::command(uint8_t inputCommand) {

    sleep_us(500);
    gpio_put(RS_PIN_, 0);
    pio_sm_put_blocking(pio0, 0, inputCommand);
    sleep_us(500);
 }

void ST7920::data(uint8_t inputData) {

    gpio_put(RS_PIN_, 1);
    pio_sm_put_blocking(pio0, 0, inputData);
}

void ST7920::fillBitmap(uint8_t* inputBitmap) {

        for (int y = 0; y < 64; y++) {
        if (y < 32) {
            command(0x80 | y);
            command(0x80);
            for (int i = 0; i < 16; i++)
                data(inputBitmap[i + y*16]);
        }
        else {
            command(0x80 | y - 32);
            command(0x88);
            for (int i = 0; i < 16; i++)
                data(inputBitmap[i + y*16]);
        }
    }
}

void ST7920::clearScreen() {

    for (int y = 0; y < 64; y++) {
        if (y < 32) {
            command(0x80 | y);
            command(0x80);
            for (int i = 0; i < 16; i++)
                data(0x00);
        }
        else {
            command(0x80 | y - 32);
            command(0x88);
            for (int i = 0; i < 16; i++)
                data(0x00);
        }
    }
}

void ST7920::graphics(bool enable) {

    if (enable) {
        command(ST7920_BASIC);
        command(ST7920_EXTEND);
        command(ST7920_GFXMODE);
    } else {
        command(ST7920_BASIC);
    }
}

void ST7920::writeText(uint8_t col, uint8_t row, char* string)
{

    switch (row) {
        case 0:
            col |= ST7920_LINE0;
            break;
        case 1:
            col |= ST7920_LINE1;
            break;
        case 2:
            col |= ST7920_LINE2;
            break;
        case 3:
            col |= ST7920_LINE3;
            break;
        default:
            col |= ST7920_LINE0;
            break;
    }

    //sleep_us(500);
    command(col);
    //sleep_us(500);

    while (*string)
        data(*string++);
}

void ST7920::init() {

    gpio_put(RST_PIN_, 1);
    sleep_ms(100);
    gpio_put(RST_PIN_, 0);

    sleep_ms(50);

    command(0b00000010);// 4-bit mode.
    sleep_ms(10);
	command(0b00000010);// 4-bit mode.
    sleep_ms(10);

    command(ST7920_DISPLAYON);// Cursor and blinking cursor disabled.
    sleep_ms(1);
    command(ST7920_CLS);// Clears screen.
    sleep_ms(10);
    command(ST7920_ADDRINC);// Cursor moves right, no display shift. 
    command(ST7920_HOME);// Returns to home. Cursor moves to starting point.
    sleep_ms(20);
}
