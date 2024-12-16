#include "index.h"

vec2_t
spring_force(vec2_t first, vec2_t second) {
    double delta_x = second.x - first.x;
    double delta_y = second.y - first.y;

    double distance_sqared = delta_x * delta_x + delta_y * delta_y;
    double distance = sqrt(distance_sqared);

    double C = 0.03;
    double spring_length = 5;

    double factor = log(fabs(distance / spring_length));

    double force_x = C * factor * delta_x;
    double force_y = C * factor * delta_y;

    // printf("[spring_delta] C: %f, factor: %f\n", C, factor);
    // printf("[spring_delta] delta_x: %f, delta_y: %f\n", delta_x, delta_y);
    // printf("[spring_force] force_x: %f, force_y: %f\n", force_x, force_y);

    if (isnan(force_x) || isnan(force_y)) {
        return (vec2_t) { .x = 0, .y = 0 };
    }

    return (vec2_t) {
        .x = force_x,
        .y = force_y,
    };
}
