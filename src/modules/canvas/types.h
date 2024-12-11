#pragma once

// About the four colors:
// - https://wiki.xxiivv.com/site/theme.html

typedef enum {
    BG_COLOR = 0, // Background/alpha
    SL_COLOR = 1, // Selection
    FG_COLOR = 2, // Foreground
    AP_COLOR = 3, // Application
} color_t;

// blending naming:
//     <BG_COLOR>_<AP_COLOR><VARIANT>

typedef enum {
    TR_FG_BLENDING = 0,
    BG_AP_BLENDING,
    BG_SL_BLENDING,
    BG_FG2_BLENDING,

    SL_FG_BLENDING,
    TR_AP_BLENDING,
    SL_SL_BLENDING,
    SL_FG2_BLENDING,

    FG_FG_BLENDING,
    FG_AP_BLENDING,
    TR_SL_BLENDING,
    FG_FG2_BLENDING,

    AP_FG_BLENDING,
    AP_AP_BLENDING,
    AP_SL_BLENDING,
    TR_FG2_BLENDING,
} blending_t;

typedef enum {
    SM_ROUNDNESS,
} roundness_t;

typedef struct canvas_t canvas_t;
typedef struct canvas_window_t canvas_window_t;
typedef struct clickable_area_t clickable_area_t;
typedef struct cursor_t cursor_t;
