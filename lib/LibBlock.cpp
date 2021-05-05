#include <LibBlock.h>

#include <X11/Xlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void set_x_root(const char* text)
{
    Display* dpy = XOpenDisplay(NULL);
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

const char* Block::cmd() const { return Block::m_command; }

u32 Block::interval() const { return Block::m_interval; }

u32 Block::signal() const { return Block::m_signal; }

u32 Block::time_since_last_updated_in_sec() const { return Block::m_time_since_last_updated_in_sec; }

void Block::set_time_since_last_updated_in_sec(u32 time) { Block::m_time_since_last_updated_in_sec = time; }

char* Block::last_output() const { return Block::m_last_output; }

void Block::set_last_output(char* output) { Block::m_last_output = output; }

char* Block::cmd_output() const
{
    char* buf = static_cast<char*>(calloc(126, sizeof(char)));

    char* which_cmd = static_cast<char*>(calloc(strlen("which ") + strlen(this->cmd()) + strlen(">/dev/null 2>/dev/null") + 1, sizeof(char)));
    strcpy(which_cmd, "which ");
    strcat(which_cmd, this->cmd());
    strcat(which_cmd, ">/dev/null 2>/dev/null");

    if (system(which_cmd) == 0) {
        FILE* fd = popen(this->cmd(), "r");
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
    if (this->last_output() == NULL) {
        this->set_last_output(this->cmd_output());
    }
    if (this->time_since_last_updated_in_sec() >= this->interval()) {
        this->set_time_since_last_updated_in_sec(0);

        this->set_last_output(this->cmd_output());

        return this->last_output();
    } else {
        this->set_time_since_last_updated_in_sec(this->time_since_last_updated_in_sec() + 1);
        return this->last_output();
    }

}
