# rpi-pico-st7920-pio
### Another basic demonstration of the Raspberry Pi Pico's PIO module.

This is another attempt to use the PIO module in the Raspberry Pi Pico to control the ST7920 display module in 4-bit parallel mode.

As usual, the PIO module handles all the pulsing of E pin and splitting the command/data into two nibbles.

GPIO pins used:

|gpio   |st7920 pins   |
|---|---|
|18-21   | D4-D7 |
|15   | E  |
|14   | RS  |
|22   | RST  |

If you cannot get the screen to print properly, try increasing the value in the clkdiv in st7920_4bp.pio. (Default is 512)

The code is ported from this website: https://tutorial.cytron.io/2012/01/02/graphic-lcd-st7920-interfacing-to-skpic32/
