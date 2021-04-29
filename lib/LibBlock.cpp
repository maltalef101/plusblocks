#include <LibBlock.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

void set_x_root(const char* text)
{
    Display *dpy = XOpenDisplay(NULL);
    i32 screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy, screen);
    XStoreName(dpy, root, text);
    XCloseDisplay(dpy);
}

Block::Block(const char* command, u32 interval, i32 signal)
{
    m_command = command;
    m_interval = interval;
    m_signal = signal;
    m_time_since_last_updated_in_sec = 0;
}

const char* Block::cmd() { return Block::m_command; }

u32 Block::interval() { return Block::m_interval; }

u32 Block::signal() { return Block::m_signal; }

u32 Block::time_since_last_updated_in_sec() { return Block::m_time_since_last_updated_in_sec; }

void Block::set_time_since_last_updated_in_sec(u32 time) { Block::m_time_since_last_updated_in_sec = time; }

char* Block::cmd_output()
{
    char *buf = static_cast<char*>(calloc(1, 126));

    char *which_cmd = static_cast<char*>(calloc(strlen("which ") + strlen(this->cmd()) + strlen(">/dev/null 2>/dev/null") + 1, sizeof(char)));
    strcpy(which_cmd, "which ");
    strcat(which_cmd, this->cmd());
    strcat(which_cmd, ">/dev/null 2>/dev/null");

    if (system(which_cmd) == 0) {
        FILE *fd = popen(this->cmd(), "r");
        fread(buf, 126, 1, fd);
        pclose(fd);
    } else {
        printf("\x1b[1m\x1b[31m[ERROR]\x1b[0m command '%s' doesn't exist, or is not in PATH\n", this->cmd());
    }
    free(which_cmd);

    return buf;
}

char* Block::update_output()
{
   Block::set_time_since_last_updated_in_sec(0);
   return this->cmd_output();
}
