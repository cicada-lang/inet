#include "index.h"

static vec2_t
electrical_force(vec2_t first, vec2_t second) {
    vec2_t delta = vec2_sub(second, first);
    double distance_sqared = vec2_square(delta);
    double distance = sqrt(distance_sqared);

    double C = 5000;
    vec2_t unit = vec2_div_scalar(delta, distance);
    vec2_t force = vec2_mul_scalar(unit, -(C / distance_sqared));;

    if (vec2_is_nan(force))
        return vec2_zero();

    return force;
}

void
node_fake_electrical_force(node_physics_t *self, hash_t *node_model_hash) {
    (void) self;

    list_t *node_model_list = hash_value_list(node_model_hash);
    node_model_t *node_model = hash_first(node_model_hash);
    while (node_model) {
        node_model_t *node_model2 = list_first(node_model_list);
        while (node_model2) {
            if (node_model2 != node_model) {
                vec2_t force = electrical_force(node_model->position, node_model2->position);

                node_model->force.x += force.x;
                node_model->force.y += force.y;
            }

            node_model2 = list_next(node_model_list);
        }

        node_model = hash_next(node_model_hash);
    }

    list_destroy(&node_model_list);
}
