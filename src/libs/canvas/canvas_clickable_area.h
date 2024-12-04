#pragma once

struct canvas_clickable_area_t {
    size_t x, y;
    size_t width, height;
    on_click_t *on_click;
};
