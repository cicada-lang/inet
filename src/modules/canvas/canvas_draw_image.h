#pragma once

// The width and height of image are measured in tile.

void canvas_draw_icn_bytes(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, blending_t blending);
void canvas_draw_chr_bytes(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, blending_t blending);

void canvas_draw_image(canvas_t *self, size_t x, size_t y, const char *path, blending_t blending);
void canvas_draw_image_button(canvas_t *self, size_t x, size_t y, const char *path, blending_t blending, on_click_fn_t *on_click);
