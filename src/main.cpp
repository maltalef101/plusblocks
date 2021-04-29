#include <LibBlock.h>
#include <stdio.h>

#include "config.h"

int main()
{
     for (u32 i = 0; i < LENGTH(blocks); i++)
    {
        Block block = blocks[i];
        char* cmd_output = block.cmd_output();
        printf("block %i: command => '%s' interval => '%i' signal => '%u' output => '%s'\n", i, block.cmd(), block.interval(), block.signal(), cmd_output);
        free(cmd_output);
    }
    return 0;
};

