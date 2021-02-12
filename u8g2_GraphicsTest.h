#ifndef U8G2_GRAPHICSTEST_H
#define U8G2_GRAPHICSTEST_H

void u8g2_prepare(u8g2_t *u8g2);
void u8g2_box_frame(u8g2_t *u8g2, uint8_t a);
void u8g2_disc_circle(u8g2_t *u8g2, uint8_t a);
void u8g2_r_frame(u8g2_t *u8g2, uint8_t a);
void u8g2_string(u8g2_t *u8g2, uint8_t a);
void u8g2_line(u8g2_t *u8g2, uint8_t a);
void u8g2_triangle(u8g2_t *u8g2, uint8_t a);
void u8g2_ascii_1(u8g2_t *u8g2);
void u8g2_ascii_2(u8g2_t *u8g2);
void u8g2_extra_page(u8g2_t *u8g2, uint8_t a);
void u8g2_bitmap_overlay(u8g2_t *u8g2, uint8_t a);
void u8g2_bitmap_modes(u8g2_t *u8g2, uint8_t transparent);
void draw(u8g2_t *u8g2, uint16_t& draw_state);

#endif
