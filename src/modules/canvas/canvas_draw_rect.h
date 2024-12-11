#pragma once

void canvas_draw_rect(canvas_t *self, size_t x, size_t y, size_t width, size_t height, size_t thickness, uint32_t pixel);
void canvas_draw_rect_round(canvas_t *self, size_t x, size_t y, size_t width, size_t height, size_t thickness, uint32_t pixel, roundness_t roundness);
