#pragma once

using u32 = unsigned int;
using i32 = int;

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>

#ifdef __OpenBSD__
#define SIGPLUS SIGUSR1+1
#define SIGMINUS SIGUSR1-1
#else
#define SIGPLUS SIGRTMIN
#define SIGMINUS SIGRTMIN
#endif

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define MIN( a, b ) ( (a < b) ? a : b )
#define CMDLENGTH 50
#define STATUSLENGTH (LENGTH(blocks) * CMDLENGTH + 1)

void set_x_root(const char*);

class Block {
public:
    Block(const char*, u32, i32);

    const char* cmd();
    u32 interval();
    u32 signal();

    u32 time_since_last_updated_in_sec();
    void set_time_since_last_updated_in_sec(u32);

    char* cmd_output();
    char* update_output();
private:
    const char* m_command;
    u32 m_interval;
    i32 m_signal;
    u32 m_time_since_last_updated_in_sec = 0;
};
