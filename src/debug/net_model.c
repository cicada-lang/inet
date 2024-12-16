#include "index.h"

net_model_t *
net_model_new(size_t x, size_t y, size_t width, size_t height) {
    net_model_t *self = new(net_model_t);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;

    self->node_model_list =
        list_new_with((destroy_fn_t *) node_model_destroy);

    self->evolving_step = 0;
    self->max_evolving_step = 1000;
    self->cooling_factor = 0.999;
    return self;
}

void
net_model_destroy(net_model_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_model_t *self = *self_pointer;
        list_destroy(&self->node_model_list);
        free(self);
        *self_pointer = NULL;
    }
}

node_model_t *
net_model_find_node_model(const net_model_t *self, const node_t *node) {
    node_model_t *node_model = list_first(self->node_model_list);
    while (node_model) {
        if (node_model->node == node)
            return node_model;

        node_model = list_next(self->node_model_list);
    }

    return NULL;
}

void
net_model_update(net_model_t *self) {
    if (!self->root) return;
    if (!self->root->opposite) return;
    if (!self->root->opposite->node) return;

    node_iter_t *iter = node_iter_new(self->root->opposite->node);
    list_t *new_list = list_new_with((destroy_fn_t *) node_model_destroy);
    node_t *node = node_iter_first(iter);
    while (node) {
        node_model_t *found = net_model_find_node_model(self, node);
        if (found) {
            list_push(new_list, found);
            list_remove(self->node_model_list, found);
        } else {
            size_t x = self->width * ((double) rand() / RAND_MAX);
            size_t y = self->height * ((double) rand() / RAND_MAX);
            node_model_t *node_model = node_model_new(node, (vec2_t) { .x = x, y = y });
            list_push(new_list, node_model);
        }

        node = node_iter_next(iter);
    }
    node_iter_destroy(&iter);

    list_destroy(&self->node_model_list);
    self->node_model_list = new_list;
}

static void
net_model_electrical_force(net_model_t *self) {
    list_t *copy = list_dup(self->node_model_list);
    node_model_t *node_model = list_first(self->node_model_list);
    while (node_model) {
        node_model_t *node_model2 = list_first(copy);
        while (node_model2) {
            if (node_model2 != node_model) {
                vec2_t force = electrical_force(
                    (vec2_t) { .x = node_model->position.x, .y = node_model->position.y },
                    (vec2_t) { .x = node_model2->position.x, .y = node_model2->position.y });

                node_model->force.x += force.x;
                node_model->force.y += force.y;
            }

            node_model2 = list_next(copy);
        }

        node_model = list_next(self->node_model_list);
    }

    list_destroy(&copy);
}

static void
net_model_spring_force(net_model_t *self) {
    if (!self->root) return;

    wire_iter_t *iter = wire_iter_new(self->root);
    wire_t *wire = wire_iter_first(iter);
    while (wire) {
        if (wire->node &&
            wire->opposite &&
            wire->opposite->node)
        {
            node_model_t *node_model1 =
                net_model_find_node_model(self, wire->node);
            node_model_t *node_model2 =
                net_model_find_node_model(self, wire->opposite->node);

            vec2_t force = spring_force(
                (vec2_t) { .x = node_model1->position.x, .y = node_model1->position.y },
                (vec2_t) { .x = node_model2->position.x, .y = node_model2->position.y });

            node_model1->force.x += force.x;
            node_model1->force.y += force.y;

            node_model2->force.x -= force.x;
            node_model2->force.y -= force.y;

            // printf("[net_model_spring_force] force.x %f, force.y: %f\n",
            //        force.x, force.y);
        }

        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);
}

void
net_model_evolve(net_model_t *self) {
    if (self->evolving_step > self->max_evolving_step)
        return;

    self->evolving_step++;

    (void) net_model_electrical_force;
    (void) net_model_spring_force;

    net_model_spring_force(self);
    net_model_electrical_force(self);

    double cooling = pow(self->cooling_factor, self->evolving_step);
    node_model_t *node_model = list_first(self->node_model_list);
    while (node_model) {
        node_model_apply_force(node_model, cooling);

        if (node_model->position.x > self->width)
            node_model->position.x = self->width;

        if (node_model->position.y > self->height)
            node_model->position.y = self->height;

        node_model = list_next(self->node_model_list);
    }
}
