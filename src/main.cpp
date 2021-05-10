#include <LibBlock.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"


static constexpr size_t SIZE_LIMIT = 47;

static bool status_continue = true;

void termhandler(i32);
void termhandler(i32)
{
    status_continue = false;
}

static void status_loop();
static void status_loop()
{
    while (status_continue) {
        char* root_str = static_cast<char*>(calloc(sizeof(char), 1024));
        for (u32 i = 0; i < LENGTH(blocks); i++) {
            Block block = blocks[i];
            char* cmd_output = block.update_output();
            if (strlen(cmd_output) >= SIZE_LIMIT)
                cmd_output[SIZE_LIMIT] = '\0';
            if (i == 0) {
                strcpy(root_str, cmd_output);
            } else {
                strcat(root_str, delim);
                strcat(root_str, cmd_output);
            }
            free(cmd_output);
        }
        sleep(1);
        // set_x_root(root_str);
        printf("%s\n", root_str);
        printf("%ld\n", time(0));
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
    status_loop();
    signal(SIGINT, termhandler);
    return 0;
};
