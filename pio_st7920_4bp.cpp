#include <stdio.h>
#include <type_traits>

#include "pico/stdlib.h"
#include "hardware/pio.h"
// Our assembled program:
#include "st7920_4bp.pio.h"

#include "picture.h"

const uint E_PIN = 15;
const uint RS_PIN = 14;
const uint RST_PIN = 22;
const uint D4_PIN = 18;

extern "C" {
    int main();
}

void st7920_command(uint8_t inputCommand) {

    sleep_us(500);
    gpio_put(RS_PIN, 0);
    pio_sm_put_blocking(pio0, 0, inputCommand);
    sleep_us(500);
 }

void st7920_data(uint8_t inputData) {
    gpio_put(RS_PIN, 1);
    pio_sm_put_blocking(pio0, 0, inputData);
}

void st7920_fillBitmap(uint8_t* inputBitmap) {

        for (int y = 0; y < 64; y++) {
        if (y < 32) {
            st7920_command(0x80 | y);
            st7920_command(0x80);
            for (int i = 0; i < 16; i++)
                st7920_data(inputBitmap[i + y*16]);
        }
        else {
            st7920_command(0x80 | y - 32);
            st7920_command(0x88);
            for (int i = 0; i < 16; i++)
                st7920_data(inputBitmap[i + y*16]);
        }
    }

}

void st7920_clearScreen() {

    for (int y = 0; y < 64; y++) {
        if (y < 32) {
            st7920_command(0x80 | y);
            st7920_command(0x80);
            for (int i = 0; i < 16; i++)
                st7920_data(0x00);
        }
        else {
            st7920_command(0x80 | y - 32);
            st7920_command(0x88);
            for (int i = 0; i < 16; i++)
                st7920_data(0x00);
        }
    }
}

void st7920_graphics(bool enable) {
    if (enable) {
        st7920_command(0x20);
        st7920_command(0x24);
        st7920_command(0x26);
    } else {
        st7920_command(0x20);
    }
}

void st7920_writeText(uint8_t col, uint8_t row, char* string)
{
    switch (row) {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0x90;
            break;
        case 2:
            col |= 0x88;
            break;
        case 3:
            col |= 0x98;
            break;
        default:
            col |= 0x80;
            break;
    }

    //sleep_us(500);
    st7920_command(col);
    //sleep_us(500);

    while (*string)
        st7920_data(*string++);
}

void st7920_init() {
    gpio_put(RST_PIN, 1);
    sleep_ms(100);
    gpio_put(RST_PIN, 0);

    sleep_ms(50);

    st7920_command(0b00000010);// 4-bit mode.
    sleep_ms(10);
	st7920_command(0b00000010);// 4-bit mode.
    sleep_ms(10);

    st7920_command(0b00001100);// Cursor and blinking cursor disabled.
    sleep_ms(1);;
    st7920_command(0b00000001);// Clears screen.
    sleep_ms(10);
    st7920_command(0b00000110);// Cursor moves right, no display shift. 
    st7920_command(0b00000010);// Returns to home. Cursor moves to starting point.
    sleep_ms(20);
}

int main()
{   
    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(RST_PIN);
    gpio_set_dir(RST_PIN, GPIO_OUT);

    gpio_init(RS_PIN);
    gpio_set_dir(RS_PIN, GPIO_OUT);
    gpio_put(RS_PIN, 0);

     // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &st7920_4bp_program);

    st7920_4bp_program_init(pio, 0, offset, E_PIN, D4_PIN);

    stdio_init_all();

    st7920_init();

    //st7920_command(0x80);
    //sleep_ms(10);
    st7920_writeText(0,0, (char*)"hello world");
    st7920_writeText(0,1, (char*)"raspberry pico");

    sleep_ms(3000);

    st7920_command(0x01);
    st7920_graphics(true);
    st7920_clearScreen();
    st7920_fillBitmap((uint8_t*)graphic);
    
    while(1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
