#include <LibBlock.h>

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <X11/Xlib.h>

#include "../src/config.h"

static Display *dpy;
static i32 screen;
static Window root;

Block::Block(const char* command, u32 interval, i32 signal)
{
    m_command = command;
    m_interval = interval;
    m_signal = signal;
};

const char* Block::get_cmd() { return Block::m_command; };

i32 Block::get_interval() { return Block::m_interval; };

u32 Block::get_sig() { return Block::m_signal; };
