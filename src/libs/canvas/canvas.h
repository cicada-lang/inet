#pragma once

// About the four colors:
// - https://wiki.xxiivv.com/site/theme.html

typedef enum {
    BG_COLOR = 0, // Background/alpha
    SL_COLOR = 1, // Selection
    FG_COLOR = 2, // Foreground
    AP_COLOR = 3, // Application
} color_t;

typedef void (on_key_t)(void *state, canvas_t *canvas, const char *key_name, bool is_release);
typedef void (on_click_t)(void *state, canvas_t *canvas, size_t x, size_t y, uint8_t button, bool is_release);
typedef void (on_frame_t)(void *state, canvas_t *canvas, uint64_t passed);

// The width and height of canvas are measured in tile.
struct canvas_t {
    size_t width, height;

    // scale defines the ratio between
    // canvas pixel and screen pixel.
    size_t scale;

    uint32_t *pixels;
    uint32_t palette[4];

    canvas_window_t *window;
    const char *title;

    size_t frame_rate;
    void *state;
    on_key_t *on_key;
    on_click_t *on_click;
    on_frame_t *on_frame;
    list_t *clickable_area_list;

    store_t *asset_store;
};

canvas_t *canvas_new(size_t width, size_t height, size_t scale);
void canvas_destroy(canvas_t **self_pointer);

void canvas_init_asset_store(canvas_t *self, const char *base);
uint8_t *canvas_asset_store_get(canvas_t *self, const char *path);

void canvas_open(canvas_t *self);

void canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_draw_pixel(canvas_t *self, size_t x, size_t y, color_t color);

void canvas_add_clickable_area(
    canvas_t *self,
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_t *on_click);
void canvas_clear_clickable_area(canvas_t *self);
