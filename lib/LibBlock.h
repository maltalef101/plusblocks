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

class Block {
public:
    const char* get_cmd();
    u32 get_sig();
    i32 get_interval();
    void setroot();

    Block(const char*, u32, i32);
private:
    const char* m_command;
    u32 m_interval;
    i32 m_signal;
};
