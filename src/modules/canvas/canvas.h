#pragma once

typedef void (on_key_fn_t)(void *state, canvas_t *canvas, const char *key_name, bool is_release);
typedef void (on_click_fn_t)(void *state, canvas_t *canvas, uint8_t button, bool is_release);
typedef void (on_frame_fn_t)(void *state, canvas_t *canvas, uint64_t passed);

// The width and height of canvas are measured in tile.
struct canvas_t {
    size_t width, height;
    cursor_t *cursor;
    bool hide_system_cursor;

    // scale defines the ratio between
    // canvas pixel and screen pixel.
    size_t scale;

    uint32_t *pixels;
    uint32_t palette[4];

    canvas_window_t *window;
    const char *title;

    size_t frame_rate;
    void *state;
    on_key_fn_t *on_key;
    on_click_fn_t *on_click;
    on_frame_fn_t *on_frame;
    list_t *clickable_area_list;

    store_t *asset_store;

    const font_t *font;
};

canvas_t *canvas_new(size_t width, size_t height, size_t scale);
void canvas_destroy(canvas_t **self_pointer);

void canvas_init_asset_store(canvas_t *self, const char *base);
blob_t *canvas_asset_store_get(canvas_t *self, const char *path);

void canvas_open(canvas_t *self);

void canvas_draw_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_draw_color(canvas_t *self, size_t x, size_t y, color_t color, blending_t blending);

void canvas_add_clickable_area(
    canvas_t *self,
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_fn_t *on_click);
void canvas_clear_clickable_area(canvas_t *self);
