#include "index.h"

static vec2_t
electrical_force(vec2_t first, vec2_t second) {
    vec2_t delta = vec2_sub(second, first);
    double distance_sqared = vec2_square(delta);
    double distance = sqrt(distance_sqared);

    double unit_x = delta.x / distance;
    double unit_y = delta.y / distance;

    double C = 5000;

    double force_x = -(C / distance_sqared) * unit_x;
    double force_y = -(C / distance_sqared) * unit_y;

    if (isnan(force_x) || isnan(force_y)) {
        return vec2_zero();
    }

    return (vec2_t) {
        .x = force_x,
        .y = force_y,
    };
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
