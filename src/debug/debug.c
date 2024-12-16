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

    self->node_hash = hash_new();
    self->node_model_hash = hash_new();
    hash_set_destroy_fn(self->node_model_hash, (destroy_fn_t *) node_model_destroy);

    size_t padding_x = 2 * TILE;
    size_t padding_y = 2 * TILE;
    self->node_physics = node_physics_new(
        padding_x,
        padding_y,
        WIDTH - padding_x * 2,
        HEIGHT - padding_y * 2);

    return self;
}

void
debug_destroy(debug_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        debug_t *self = *self_pointer;
        canvas_destroy(&self->canvas);
        hash_destroy(&self->node_model_hash);
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
draw_node(debug_t *self, canvas_t *canvas, size_t node_id, node_model_t *node_model) {
    node_t *node = hash_get(self->node_hash, (void *) node_id);
    if (!node) return;
    text_t *text = text_from_string(node->spec->name);
    size_t text_width = font_text_width(canvas->font, text);
    size_t text_height = 16;
    size_t x_padding = TILE / 2;
    size_t y_padding = 2;

    size_t x = self->node_physics->x + node_model->position.x - (text_width / 2);
    size_t y = self->node_physics->y + node_model->position.y - (text_height / 2);

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

    node_model_t *node_model1 =
        hash_get(self->node_model_hash, (void *) wire->node->id);
    node_model_t *node_model2 =
        hash_get(self->node_model_hash, (void *) wire->opposite->node->id);

    if (node_model1 && node_model2) {
        canvas_draw_line(
            canvas,
            self->node_physics->x + node_model1->position.x,
            self->node_physics->y + node_model1->position.y,
            self->node_physics->x + node_model2->position.x,
            self->node_physics->y + node_model2->position.y,
            canvas->palette[AP_COLOR]);
    }
}

static void
draw_net_border(debug_t *self, canvas_t *canvas, bool really) {
    if (!really) return;

    size_t thickness = 1;
    canvas_draw_rect_round(
        canvas,
        self->node_physics->x,
        self->node_physics->y,
        self->node_physics->width,
        self->node_physics->height,
        thickness,
        canvas->palette[AP_COLOR],
        SM_ROUNDNESS);
}

static void
draw_net(debug_t *self, canvas_t *canvas) {
    assert(self->node_physics);

    if (!self->node_physics->root)
        return;

    node_physics_fake_simulate(
        self->node_physics,
        self->node_model_hash);

    draw_net_border(self, canvas, false);

    wire_iter_t *iter = wire_iter_new(self->node_physics->root);
    wire_t *wire = wire_iter_first(iter);

    while (wire) {
        draw_wire(self, canvas, wire);
        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);

    node_model_t *node_model = hash_first(self->node_model_hash);
    while (node_model) {
        size_t node_id = (size_t) hash_cursor(self->node_model_hash);
        draw_node(self, canvas, node_id, node_model);
        node_model = hash_next(self->node_model_hash);
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
init_node_hash(debug_t *self) {
    hash_purge(self->node_hash);

    wire_t *root = stack_top(self->worker->value_stack);
    if (!root) return;
    if (!root->opposite) return;
    if (!root->opposite->node) return;

    node_iter_t *iter = node_iter_new(root->opposite->node);
    node_t *node = node_iter_first(iter);
    while (node) {
        hash_set(self->node_hash, (void *) node->id, node);
        node = node_iter_next(iter);
    }
    node_iter_destroy(&iter);
}

static void
init_node_physics(debug_t *self) {
    if (stack_is_empty(self->worker->value_stack))
        return;

    wire_t *wire = stack_top(self->worker->value_stack);
    self->node_physics->root = wire;
    node_physics_add_more_nodes(
        self->node_physics,
        self->node_hash,
        self->node_model_hash);
}

void
debug_start(worker_t *worker) {
    srand(time(NULL));

    debug_t *self = debug_new(worker);
    init_node_hash(self);
    init_node_physics(self);

    init_canvas_theme(self->canvas);
    init_canvas_asset_store(self->canvas);
    init_canvas_font(self->canvas);
    self->canvas->on_frame = (on_frame_fn_t *) on_frame;

    canvas_open(self->canvas);

    debug_destroy(&self);
}
