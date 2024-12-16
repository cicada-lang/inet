#include "index.h"



debug_t *
debug_new(worker_t *worker) {
    debug_t *self = new(debug_t);
    self->worker = worker;

    size_t width = 90 * TILE;
    size_t height = 60 * TILE;
    size_t scale = 3;

    canvas_t *canvas = canvas_new(width, height, scale);
    canvas->state = self;
    canvas->title = "inet debug";
    self->canvas = canvas;

    self->node_hash = hash_new();
    self->node_model_hash = hash_new();
    hash_set_destroy_fn(self->node_model_hash, (destroy_fn_t *) node_model_destroy);

    size_t padding_x = 4 * TILE;
    size_t padding_y = 4 * TILE;
    self->node_physics = node_physics_new(
        padding_x,
        padding_y,
        width - padding_x * 2,
        height - padding_y * 2);

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
    canvas->palette[BG_COLOR] = 0xff000000;
    canvas->palette[SL_COLOR] = 0xffcd2e3a;
    canvas->palette[FG_COLOR] = 0xff000000;
    canvas->palette[AP_COLOR] = 0xffffffff;
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
draw_background_grid(debug_t *self, canvas_t *canvas, bool really) {
    if (!really) return;

    (void) self;

    for (size_t i = 0; i < canvas->width / TILE; i++) {
        for (size_t j = 0; j < canvas->height / TILE; j++) {
            canvas_draw_pixel(canvas, i * TILE, j * TILE, 0xffff0000);
        }
    }
}

static void
on_frame(debug_t *self, canvas_t *canvas, uint64_t passed) {
    (void) passed;

    canvas->window->background_pixel = canvas->palette[AP_COLOR];
    canvas_fill_bottom_right(canvas, 0, 0, canvas->palette[AP_COLOR]);
    canvas_clear_clickable_area(canvas);

    draw_background_grid(self, canvas, false);
    draw_net(self, canvas);
    draw_step_button(self, canvas);
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
