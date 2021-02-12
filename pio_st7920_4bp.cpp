#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
// Our assembled program:
#include "st7920_4bp.pio.h"

extern "C" {
#include "u8g2.h"
}

#include "st7920.h"
#include "picture.h"
#include "u8g2_hal_rpi_pico.h"
#include "u8g2_GraphicsTest.h"

const uint E_PIN = 15;
const uint RS_PIN = 14;
const uint RST_PIN = 22;
const uint D4_PIN = 18;

extern "C" int main()
{   
    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(RST_PIN);
    gpio_set_dir(RST_PIN, GPIO_OUT);

    gpio_init(RS_PIN);
    gpio_set_dir(RS_PIN, GPIO_OUT);
    gpio_put(RS_PIN, 0);

    u8g2_t u8g2;

     // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &st7920_4bp_program);

    st7920_4bp_program_init(pio, 0, offset, E_PIN, D4_PIN);

    stdio_init_all();

    ST7920 st7920(D4_PIN, E_PIN, RS_PIN, RST_PIN);

    st7920.init();
    st7920.graphics(true);
    st7920.clearScreen();

    u8g2_Setup_st7920_p_128x64_f(&u8g2, U8G2_R0, cb_byte_pio_hw, cb_gpio_delay_rpi);
   
    u8g2_InitDisplay(&u8g2);

    // Getting the frame buffer pointer to manually fill screen.   
    uint8_t* frameBufferPtr = u8g2_GetBufferPtr(&u8g2);

    // Getting the info about U8G2's ST7920 framebuffer:
    // uint16_t bufferTileHeight = u8g2_GetBufferTileHeight(&u8g2);
    // uint16_t bufferTileWidth = u8g2_GetBufferTileWidth(&u8g2);
    // bufferSize = 1024
    // tileHeight = 8
    // tileWidth = 16
    // uint32_t bufferSize = 8 * tileHeight * tileWidth;
  
    u8g2_ClearBuffer(&u8g2);

    // u8g2_SendBuffer(&u8g2);
    // U8G2 SendBuffer only uses 8-bit parallel and SPI. Bypassing it and using the bitmap fill instead.
    st7920.fillBitmap(frameBufferPtr);

    // U8G2 test program ported from https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_full_buffer/GraphicsTest/GraphicsTest.ino:    
    uint16_t draw_state = 0;
    
    while(1) {
        u8g2_ClearBuffer(&u8g2);
        draw(&u8g2, draw_state);
        st7920.fillBitmap(frameBufferPtr);

        // increase the state
        draw_state++;
        if (draw_state >= (12 * 8))
            draw_state = 0;

        // deley between each page
        sleep_ms(25);
    }

    return 0;
}
