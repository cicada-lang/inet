#include "index.h"

canvas_t *
canvas_new(size_t width, size_t height, size_t scale) {
    canvas_t *self = new(canvas_t);

    self->width = width;
    self->height = height;
    self->scale = scale;

    self->pixels = allocate(width * height * sizeof(uint32_t));

    self->palette[BG_COLOR] = 0xff0047A0;
    self->palette[SL_COLOR] = 0xffcd2e3a;
    self->palette[FG_COLOR] = 0xff000000;
    self->palette[AP_COLOR] = 0xffffffff;

    self->window = canvas_window_new(self);
    self->frame_rate = 60;

    self->clickable_area_list = list_new_with(
        (destructor_t *) clickable_area_destroy);

    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self->pixels);
        canvas_window_destroy(&self->window);
        list_destroy(&self->clickable_area_list);
        store_destroy(&self->asset_store);
        free(self);
        *self_pointer = NULL;
    }
}

void
canvas_init_asset_store(canvas_t *self, const char *base) {
    assert(!self->asset_store);
    self->asset_store = store_new(base);
}

uint8_t *
canvas_asset_store_get(canvas_t *self, const char *path) {
    return store_get(self->asset_store, path);
}

void
canvas_open(canvas_t *self) {
    canvas_window_open(self->window);
}

void
canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    self->pixels[y * self->width + x] = pixel;
}

void
canvas_draw_pixel(canvas_t *self, size_t x, size_t y, color_t color) {
    canvas_put_pixel(self, x, y, self->palette[color]);
}

void
canvas_add_clickable_area(
    canvas_t *self,
    size_t x, size_t y,
    size_t width, size_t height,
    on_click_t *on_click
) {
    clickable_area_t *clickable_area =
        clickable_area_new(x, y, width, height, on_click);
    list_push(self->clickable_area_list, clickable_area);
}

void
canvas_clear_clickable_area(canvas_t *self) {
    list_purge(self->clickable_area_list);
}
