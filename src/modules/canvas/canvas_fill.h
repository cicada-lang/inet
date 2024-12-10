#pragma once

void canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_fill_top_right(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_fill_top_left(canvas_t *self, size_t x, size_t y, uint32_t pixel);

void canvas_fill_rect(canvas_t *self, size_t x, size_t y, size_t width, size_t height, uint32_t pixel);
void canvas_draw_rect(canvas_t *self, size_t x, size_t y, size_t width, size_t height, size_t thickness, uint32_t pixel);
