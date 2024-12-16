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
        10 * TILE,
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
draw_node(debug_t *self, canvas_t *canvas, node_model_t *node_model) {
    text_t *text = text_from_string(node_model->node->spec->name);
    size_t text_width = font_text_width(canvas->font, text);
    size_t text_height = 16;
    size_t x_padding = TILE / 2;
    size_t y_padding = 2;

    size_t x = self->net_layout->x + node_model->x - (text_width / 2);
    size_t y = self->net_layout->y + node_model->y - (text_height / 2);

    size_t width = text_width + x_padding * 2;
    size_t height = 2 * TILE;

    canvas_fiil_rect_round(
        canvas,
        x - x_padding,
        y - y_padding,
        width,
        height + y_padding * 2,
        canvas->palette[FG_COLOR],
        SM_ROUNDNESS);

    size_t thickness = 1;
    canvas_draw_rect_round(
        canvas,
        x - x_padding,
        y - y_padding,
        width,
        height + y_padding * 2,
        thickness,
        canvas->palette[AP_COLOR],
        SM_ROUNDNESS);

    size_t scale = 1;
    canvas_draw_text(canvas, x, y, text, scale, BG_AP_BLENDING);
    text_destroy(&text);
}

static void
draw_wire(debug_t *self, canvas_t *canvas, const wire_t *wire) {
    if (!wire->node ||
        !wire->opposite ||
        !wire->opposite->node)
        return;

    net_layout_t *net_layout = self->net_layout;

    node_model_t *node_model1 =
        net_layout_find_node_model(net_layout, wire->node);
    node_model_t *node_model2 =
        net_layout_find_node_model(net_layout, wire->opposite->node);

    if (node_model1 && node_model2) {
        canvas_draw_line(
            canvas,
            net_layout->x + node_model1->x,
            net_layout->y + node_model1->y,
            net_layout->x + node_model2->x,
            net_layout->y + node_model2->y,
            canvas->palette[AP_COLOR]);
    }
}

static void
draw_net_border(debug_t *self, canvas_t *canvas) {
    net_layout_t *net_layout = self->net_layout;
    size_t thickness = 1;
    canvas_draw_rect_round(
        canvas,
        net_layout->x,
        net_layout->y,
        net_layout->width,
        net_layout->height,
        thickness,
        canvas->palette[AP_COLOR],
        SM_ROUNDNESS);
}

static void
draw_net(debug_t *self, canvas_t *canvas) {
    assert(self->net_layout);

    net_layout_t *net_layout = self->net_layout;
    if (!net_layout->root)
        return;
    net_layout_evolve(net_layout);
    draw_net_border(self, canvas);

    wire_iter_t *iter = wire_iter_new(net_layout->root);
    wire_t *wire = wire_iter_first(iter);

    while (wire) {
        draw_wire(self, canvas, wire);
        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);

    node_model_t *node_model = list_first(net_layout->node_model_list);
    while (node_model) {
        draw_node(self, canvas, node_model);
        node_model = list_next(net_layout->node_model_list);
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
    if (stack_is_empty(self->worker->value_stack))
        return;

    wire_t *wire = stack_top(self->worker->value_stack);
    self->net_layout->root = wire;
    net_layout_update(self->net_layout);
}

void
debug_start(worker_t *worker) {
    srand(time(NULL));

    debug_t *self = debug_new(worker);
    init_net_layout(self);

    init_canvas_theme(self->canvas);
    init_canvas_asset_store(self->canvas);
    init_canvas_font(self->canvas);
    self->canvas->on_frame = (on_frame_fn_t *) on_frame;

    canvas_open(self->canvas);

    debug_destroy(&self);
}
