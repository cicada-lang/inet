#pragma once

struct clickable_area_t {
    size_t x, y;
    size_t width, height;
    on_click_fn_t *on_click;
};

clickable_area_t *clickable_area_new(
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_fn_t *on_click);
void clickable_area_destroy(clickable_area_t **self_pointer);
