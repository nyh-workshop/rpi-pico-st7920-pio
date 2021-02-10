#ifndef ST7920_H
#define ST7920_H
#include <stdio.h>

// Constant names thanks to https://github.com/cbm80amiga/ST7920_SPI:
const uint8_t ST7920_CLS = 0x01;
const uint8_t ST7920_HOME = 0x02;
const uint8_t ST7920_ADDRINC = 0x06;
const uint8_t ST7920_DISPLAYON = 0x0C;
const uint8_t ST7920_DISPLAYOFF = 0x08;
const uint8_t ST7920_CURSORON = 0x0E;
const uint8_t ST7920_CURSORBLINK = 0x0F;
// 4-bit mode!
const uint8_t ST7920_BASIC = 0x20;
const uint8_t ST7920_EXTEND = 0x24;
const uint8_t ST7920_GFXMODE = 0x26;

const uint8_t ST7920_STANDBY = 0x01;
const uint8_t ST7920_SCROLL = 0x03;
const uint8_t ST7920_SCROLLADDR = 0x40;
const uint8_t ST7920_ADDR = 0x80;
const uint8_t ST7920_LINE0 = 0x80;
const uint8_t ST7920_LINE1 = 0x90;
const uint8_t ST7920_LINE2 = 0x88;
const uint8_t ST7920_LINE3 = 0x98;

class ST7920 {
    public:
    ST7920();
    ST7920(uint D4_PIN, uint E_PIN, uint RS_PIN, uint RST_PIN);
    void command(uint8_t inputCommand);
    void data(uint8_t inputData);
    void fillBitmap(uint8_t* inputBitmap);
    void clearScreen();
    void graphics(bool enable);
    void writeText(uint8_t col, uint8_t row, char* string);
    void init();

    private:
    uint D4_PIN_;
    uint E_PIN_;
    uint RS_PIN_;
    uint RST_PIN_;
    
};

#endif
