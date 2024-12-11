#include "index.h"

position_t
electrical_force(position_t first, position_t second) {
    double C = 1000 * 50;

    double delta_x = second.x - first.x;
    double delta_y = second.y - first.y;

    double distance_sqared = delta_x * delta_x + delta_y * delta_y;
    double distance = sqrt(distance_sqared);

    double unit_x = delta_x / distance;
    double unit_y = delta_y / distance;

    double force_x = -(C / distance_sqared) * unit_x;
    double force_y = -(C / distance_sqared) * unit_y;

    if (isnan(force_x) || isnan(force_y)) {
        return (position_t) { .x = 0, .y = 0 };
    }

    return (position_t) {
        .x = force_x,
        .y = force_y,
    };
}

position_t
spring_force(position_t first, position_t second) {
    double C = 1 / 30;
    double spring_length = 5;

    double delta_x = second.x - first.x;
    double delta_y = second.y - first.y;
    double distance_sqared = delta_x * delta_x + delta_y * delta_y;
    double distance = sqrt(distance_sqared);

    double factor = log(fabs(distance / spring_length));

    double force_x = C * factor * delta_x;
    double force_y = C * factor * delta_y;

    if (isnan(force_x) || isnan(force_y)) {
        return (position_t) { .x = 0, .y = 0 };
    }

    return (position_t) {
        .x = force_x,
        .y = force_y,
    };
}
