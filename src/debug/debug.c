#include "index.h"

#define WIDTH (90 * TILE)
#define HEIGHT (60 * TILE)
#define SCALE 3

debug_t *
debug_new(worker_t *worker) {
    debug_t *self = new(debug_t);
    self->worker = worker;

    canvas_t *canvas = canvas_new(WIDTH, HEIGHT, SCALE);
    canvas->state = self;
    canvas->title = "inet debug";
    self->canvas = canvas;

    self->net_layout = net_layout_new(
        15 * TILE,
        15 * TILE,
        60 * TILE,
        40 * TILE);

    return self;
}

void
debug_destroy(debug_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        debug_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        free(self);
        *self_pointer = NULL;
    }
}

static void
init_canvas_theme(canvas_t *canvas) {
    canvas->palette[BG_COLOR] = 0xffffffff;
    canvas->palette[SL_COLOR] = 0xffff8888;
    canvas->palette[FG_COLOR] = 0xffffffff;
    canvas->palette[AP_COLOR] = 0xff000000;
}

static void
init_canvas_asset_store(canvas_t *canvas) {
    char *root = dirname(dirname(dirname(string_dup(__FILE__))));
    canvas_init_asset_store(canvas, string_append(root, "/assets"));
}

static void
init_canvas_font(canvas_t *canvas) {
    blob_t *blob = canvas_asset_store_get(canvas, "fonts/unifont_all-16.0.02.hex");
    canvas->font = font_from_hex_string(blob_string(blob));
}

static void
draw_background_grid(debug_t *self, canvas_t *canvas) {
    (void) self;

    for (size_t i = 0; i < WIDTH / TILE; i++) {
        for (size_t j = 0; j < HEIGHT / TILE; j++) {
            canvas_draw_pixel(canvas, i * TILE, j * TILE, 0xffff0000);
        }
    }
}

static void
on_frame(debug_t *self, canvas_t *canvas, uint64_t passed) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);

    draw_background_grid(self, canvas);
}

static void
init_net_layout(debug_t *self) {
    wire_t *wire = stack_top(self->worker->value_stack);
    if (!wire->opposite) return;
    if (!wire->opposite->node) return;

    net_layout_update(self->net_layout, node_iter_new(wire->opposite->node));
}

void
debug_start(worker_t *worker) {
    debug_t *self = debug_new(worker);

    init_canvas_theme(self->canvas);
    init_canvas_asset_store(self->canvas);
    init_canvas_font(self->canvas);

    self->canvas->on_frame = (on_frame_t *) on_frame;

    init_net_layout(self);

    canvas_open(self->canvas);

    debug_destroy(&self);
}
