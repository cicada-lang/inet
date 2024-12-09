#pragma once

extern color_t blending_table[16][4];

// blending naming:
//     <BG_COLOR>_<AP_COLOR><VARIANT>

typedef enum {
    TR_FG_BLENDING,
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

bool blending_is_transparent(blending_t blending);
