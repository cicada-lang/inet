#include "index.h"

// About the 16 blendings:
// - https://wiki.xxiivv.com/site/varvara.html

color_t blending_table[16][4] = {
    // fg
    // ap
    // sl
    // fg2

    { 0, 0, 1, 2 }, // bg bg sl fg tr -- tr fg
    { 0, 1, 2, 3 }, // bg sl fg ap    -- bg ap
    { 0, 2, 3, 1 }, // bg fg ap sl    -- bg sl
    { 0, 3, 1, 2 }, // bg ap sl fg    -- bg fg2

    { 1, 0, 1, 2 }, // sl bg sl fg    -- sl fg
    { 0, 1, 2, 3 }, // bg sl fg ap tr -- tr ap
    { 1, 2, 3, 1 }, // sl fg ap sl    -- sl sl
    { 1, 3, 1, 2 }, // sl ap sl fg    -- sl fg2

    { 2, 0, 1, 2 }, // fg bg sl fg    -- fg fg
    { 2, 1, 2, 3 }, // fg sl fg ap    -- fg ap
    { 0, 2, 3, 1 }, // bg fg ap sl tr -- tr sl
    { 2, 3, 1, 2 }, // fg ap sl fg    -- fg fg2

    { 3, 0, 1, 2 }, // ap bg sl fg    -- ap fg
    { 3, 1, 2, 3 }, // ap sl fg ap    -- ap ap
    { 3, 2, 3, 1 }, // ap fg ap sl    -- ap sl
    { 0, 3, 1, 2 }, // bg ap sl fg tr -- tr fg2
};

bool
blending_is_transparent(blending_t blending) {
    return
        (blending == 0x0) ||
        (blending == 0x5) ||
        (blending == 0xa) ||
        (blending == 0xf);
}
