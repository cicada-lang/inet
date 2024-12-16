#pragma once

struct vec2_t { double x, y; };
typedef struct vec2_t vec2_t;

typedef struct debug_t debug_t;
typedef struct node_model_t node_model_t;
typedef struct node_physics_t node_physics_t;

typedef void (node_force_fn_t)(node_physics_t *self, hash_t *node_model_hash);
