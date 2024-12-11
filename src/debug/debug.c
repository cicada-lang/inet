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
draw_background_grid(debug_t *self, canvas_t *canvas, bool is_on) {
    if (!is_on) return;

    (void) self;

    for (size_t i = 0; i < WIDTH / TILE; i++) {
        for (size_t j = 0; j < HEIGHT / TILE; j++) {
            canvas_draw_pixel(canvas, i * TILE, j * TILE, 0xffff0000);
        }
    }
}

static void
draw_node(debug_t *self, canvas_t *canvas, node_layout_t *node_layout) {
    (void) self;

    text_t *text = text_from_string(node_layout->node->spec->name);
    size_t text_width = font_text_width(canvas->font, text);
    size_t x_padding = TILE / 2;

    size_t x = self->net_layout->x + node_layout->x - (text_width / 2);
    size_t y = self->net_layout->y + node_layout->y;

    size_t width = text_width + x_padding * 2;
    size_t height = 2 * TILE;
    size_t thickness = 1;
    uint32_t pixel = canvas->palette[AP_COLOR];
    canvas_draw_rect_round(
        canvas,
        x - x_padding,
        y,
        width, height,
        thickness, pixel,
        SM_ROUNDNESS);

    size_t scale = 1;
    canvas_draw_text(canvas, x, y, text, scale, TR_AP_BLENDING);
    text_destroy(&text);
}

// static void
// draw_edge(
//     debug_t *self,
//     canvas_t *canvas,
//     node_layout_t *node_layout1,
//     node_layout_t *node_layout2
// ) {
//     canvas_draw_line(
//         canvas,
//         self->net_layout->x + node_layout1->x,
//         self->net_layout->y + node_layout1->y,
//         self->net_layout->x + node_layout2->x,
//         self->net_layout->y + node_layout2->y,
//         canvas->palette[AP_COLOR]);
// }

static void
draw_net_border(debug_t *self, canvas_t *canvas) {
    size_t thickness = 1;
    uint32_t pixel = canvas->palette[AP_COLOR];
    canvas_draw_rect_round(
        canvas,
        self->net_layout->x,
        self->net_layout->y,
        self->net_layout->width,
        self->net_layout->height,
        thickness, pixel,
        SM_ROUNDNESS);
}

static void
draw_net(debug_t *self, canvas_t *canvas) {
    assert(self->net_layout);
    draw_net_border(self, canvas);

    node_layout_t *node_layout = list_start(self->net_layout->node_layout_list);
    while (node_layout) {
        draw_node(self, canvas, node_layout);
        node_layout = list_next(self->net_layout->node_layout_list);
    }
}

static void
on_frame(debug_t *self, canvas_t *canvas, uint64_t passed) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[BG_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[BG_COLOR]);
    canvas_clear_clickable_area(canvas);

    draw_background_grid(self, canvas, false);
    draw_net(self, canvas);
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
    init_net_layout(self);

    init_canvas_theme(self->canvas);
    init_canvas_asset_store(self->canvas);
    init_canvas_font(self->canvas);
    self->canvas->on_frame = (on_frame_t *) on_frame;

    canvas_open(self->canvas);

    debug_destroy(&self);
}
