#include "index.h"

static vec2_t
spring_force(vec2_t first, vec2_t second) {
    vec2_t delta = vec2_sub(second, first);

    double distance_sqared = delta.x * delta.x + delta.y * delta.y;
    double distance = sqrt(distance_sqared);

    double C = 0.03;
    double spring_length = 5;

    double factor = log(fabs(distance / spring_length));

    double force_x = C * factor * delta.x;
    double force_y = C * factor * delta.y;

    if (isnan(force_x) || isnan(force_y)) {
        return (vec2_t) { .x = 0, .y = 0 };
    }

    return (vec2_t) {
        .x = force_x,
        .y = force_y,
    };
}

void
node_fake_spring_force(node_physics_t *self, hash_t *node_model_hash) {
    if (!self->root) return;

    wire_iter_t *iter = wire_iter_new(self->root);
    wire_t *wire = wire_iter_first(iter);
    while (wire) {
        if (wire->node &&
            wire->opposite &&
            wire->opposite->node)
        {
            node_model_t *node_model1 = hash_get(node_model_hash, (void *) wire->node->id);
            node_model_t *node_model2 = hash_get(node_model_hash, (void *) wire->opposite->node->id);

            vec2_t force = spring_force(node_model1->position, node_model2->position);

            node_model1->force.x += force.x;
            node_model1->force.y += force.y;

            node_model2->force.x -= force.x;
            node_model2->force.y -= force.y;
        }

        wire = wire_iter_next(iter);
    }
    wire_iter_destroy(&iter);
}
