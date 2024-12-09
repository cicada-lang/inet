#include "index.h"

net_layout_t *
net_layout_new(size_t x, size_t y, size_t width, size_t height) {
    net_layout_t *self = new(net_layout_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;

    self->node_layout_list =
        list_new_with((destroy_t *) node_layout_destroy);

    self->evolving_step = 0;
    self->max_evolving_step = 100000;
    // self->cooling_factor = 0.999;
    self->cooling_factor = 1;
    return self;
}

void
net_layout_destroy(net_layout_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_layout_t *self = *self_pointer;
        list_destroy(&self->node_layout_list);
        free(self);
        *self_pointer = NULL;
    }
}

node_layout_t *
net_layout_find_node_layout(const net_layout_t *self, const node_t *node) {
    node_layout_t *node_layout = list_start(self->node_layout_list);
    while (node_layout) {
        if (node_layout->node == node)
            return node_layout;

        node_layout = list_next(self->node_layout_list);
    }

    return NULL;
}

void
net_layout_update(net_layout_t *self) {
    if (!self->root) return;
    if (!self->root->opposite) return;
    if (!self->root->opposite->node) return;

    node_iter_t *iter = node_iter_new(self->root->opposite->node);
    list_t *new_list = list_new_with((destroy_t *) node_layout_destroy);
    node_t *node = node_iter_start(iter);
    while (node) {
        node_layout_t *found = net_layout_find_node_layout(self, node);
        if (found) {
            list_push(new_list, found);
            list_remove(self->node_layout_list, found);
        } else {
            size_t x = self->width * ((double) rand() / RAND_MAX);
            size_t y = self->height * ((double) rand() / RAND_MAX);
            node_layout_t *node_layout = node_layout_new(node, x, y);
            list_push(new_list, node_layout);
        }

        node = node_iter_next(iter);
    }
    node_iter_destroy(&iter);

    list_destroy(&self->node_layout_list);
    self->node_layout_list = new_list;
}

static void
net_layout_electrical_force(net_layout_t *self) {
    list_t *copy = list_dup(self->node_layout_list);
    list_set_destroy_fn(copy, NULL);
    node_layout_t *node_layout = list_start(self->node_layout_list);

    while (node_layout) {
        node_layout_t *node_layout2 = list_start(copy);
        while (node_layout2) {
            if (node_layout2 != node_layout) {
                vec2_t force = electrical_force(
                    (vec2_t) { .x = node_layout->x, .y = node_layout->y },
                    (vec2_t) { .x = node_layout2->x, .y = node_layout2->y });

                node_layout->force.x += force.x;
                node_layout->force.y += force.y;
            }

            node_layout2 = list_next(copy);
        }

        node_layout = list_next(self->node_layout_list);
    }

    list_destroy(&copy);
}

static void
net_layout_spring_force(net_layout_t *self) {
    if (!self->root) return;

    wire_iter_t *iter = wire_iter_new(self->root);
    wire_t *wire = wire_iter_start(iter);
    while (wire) {
        if (wire->node &&
            wire->opposite &&
            wire->opposite->node)
        {
            node_layout_t *node_layout1 =
                net_layout_find_node_layout(self, wire->node);
            node_layout_t *node_layout2 =
                net_layout_find_node_layout(self, wire->opposite->node);

            vec2_t force = spring_force(
                (vec2_t) { .x = node_layout1->x, .y = node_layout1->y },
                (vec2_t) { .x = node_layout2->x, .y = node_layout2->y });

            node_layout1->force.x += force.x;
            node_layout1->force.y += force.y;

            node_layout2->force.x -= force.x;
            node_layout2->force.y -= force.y;

            // printf("[net_layout_spring_force] force.x %f, force.y: %f\n",
            //        force.x, force.y);
        }

        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);
}

void
net_layout_evolve(net_layout_t *self) {
    if (self->evolving_step > self->max_evolving_step)
        return;

    self->evolving_step++;

    (void) net_layout_electrical_force;
    (void) net_layout_spring_force;

    net_layout_spring_force(self);
    net_layout_electrical_force(self);

    double cooling = pow(self->cooling_factor, self->evolving_step);
    node_layout_t *node_layout = list_start(self->node_layout_list);
    while (node_layout) {
        node_layout_apply_force(node_layout, cooling);

        if (node_layout->x > self->width)
            node_layout->x = self->width;

        if (node_layout->y > self->height)
            node_layout->y = self->height;

        node_layout = list_next(self->node_layout_list);
    }
}
