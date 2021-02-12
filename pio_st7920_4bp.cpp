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
    u8g2_DrawRFrame(&u8g2, 1,1,126, 63, 5);
    u8g2_SetFont(&u8g2, u8g2_font_5x7_tf);
    u8g2_DrawStr(&u8g2, 22, 16,"Hello World U8G2!");
    u8g2_DrawStr(&u8g2, 22, 32,"Raspberry Pi Pico");
    u8g2_SetFont(&u8g2, u8g2_font_open_iconic_weather_2x_t);
    u8g2_DrawGlyph(&u8g2, 3, 55, 64);
    u8g2_SetFont(&u8g2, u8g2_font_open_iconic_www_2x_t);
    u8g2_DrawGlyph(&u8g2, 24, 55, 81);    
    u8g2_DrawGlyph(&u8g2, 45, 55, 78);
    u8g2_DrawGlyph(&u8g2, 66, 55, 65);
    u8g2_SetFont(&u8g2, u8g2_font_open_iconic_weather_2x_t);
    u8g2_DrawGlyph(&u8g2, 87, 55, 68);
    u8g2_DrawGlyph(&u8g2, 107, 55, 69);

    // u8g2_SendBuffer(&u8g2);
    // U8G2 SendBuffer only uses 8-bit parallel and SPI. Bypassing it and using the bitmap fill instead.
    st7920.fillBitmap(frameBufferPtr);    
    
    while(1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
