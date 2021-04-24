#include <LibBlock.h>
#include <stdio.h>

#include "config.h"

int main()
{
    for (u32 i = 0; i < LENGTH(blocks); i++)
    {
        Block block = blocks[i];
        printf("block %i: command => '%s' interval => '%i' signal => '%u'\n", i, block.get_cmd(), block.get_interval(), block.get_sig());
    }

    return 0;
};
