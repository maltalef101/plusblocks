#include <LibBlock.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "config.h"

static bool status_continue = true;

void termhandler(i32);
void termhandler(i32)
{
    status_continue = 0;
}

static void event_loop();
static void event_loop()
{
    while (status_continue) {
        char* root_str = static_cast<char*>(calloc(1024, 1));
        for (u32 i = 0; i < LENGTH(blocks); i++) {
            Block block = blocks[i];
            char* cmd_output = block.cmd_output();
            if (i == 0) {
                strcpy(root_str, cmd_output);
            } else {
                strcat(root_str, cmd_output);
            }
            free(cmd_output);
        }
        sleep(1);
        // set_x_root(root_str);
        printf("%s\n", root_str);
        free(root_str);
    }
}

int main()
{
    /* for (u32 i = 0; i < LENGTH(blocks); i++) {
        Block block = blocks[i];
        char* cmd_output = block.cmd_output();
        printf("block %i: command => '%s' interval => '%i' signal => '%u' output => '%s'\n", i, block.cmd(), block.interval(), block.signal(), cmd_output);
        free(cmd_output);
    } */
    event_loop();
    signal(SIGINT, termhandler);
    return 0;
};

