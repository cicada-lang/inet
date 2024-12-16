#include "index.h"

static vec2_t
spring_force(vec2_t first, vec2_t second) {
    vec2_t delta = vec2_sub(second, first);
    double distance = vec2_length(delta);

    double C = 0.03;
    double spring_length = 5;

    double factor = log(fabs(distance / spring_length));
    vec2_t force = vec2_mul_scalar(delta, C * factor);;

    if (vec2_is_nan(force))
        return vec2_zeros();

    return force;
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
