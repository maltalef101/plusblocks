#include <LibBlock.h>

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>

static Display *dpy;
static i32 screen;
static Window root;

Block::Block(const char* command, u32 interval, i32 signal)
{
    m_command = command;
    m_interval = interval;
    m_signal = signal;
}

const char* Block::cmd() { return Block::m_command; }

i32 Block::interval() { return Block::m_interval; }

u32 Block::sig() { return Block::m_signal; }

char* Block::cmd_output()
{
    char *buf = static_cast<char*>(malloc(126));
    FILE *fd = popen(this->cmd(), "r");
    if (fd == NULL) {
        printf("[ERROR] command '%s' doesn't exist!\n", this->cmd());
        pclose(fd);
    }
    fread(buf, 126, 1, fd);
    pclose(fd);
    return buf;
}
