#pragma once

#include <LibBlock.h>

static const Block blocks[] = {
    /*Command*/ /*Update Interval*/ /*Update Signal*/
    { "music", 3, 15 },
    { "weather", 300, 16 },
    { "clock", 1, 15 },
};

const char delim[] = " ";
