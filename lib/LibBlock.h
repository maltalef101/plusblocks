#pragma once

#include <stdlib.h>

using u32 = __UINT32_TYPE__;
using i32 = __INT32_TYPE__;

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
static constexpr u32 CMDLENGTH = 47;
#define STATUSLENGTH (LENGTH(blocks) * CMDLENGTH + 1)

void set_x_root(const char*);

class Block {
public:
    Block(const char*, u32, i32);

    const char* cmd() const;
    u32 interval() const;
    i32 signal() const;

    u32 time_since_last_updated_in_sec() const;
    void set_time_since_last_updated_in_sec(u32);

    char* cmd_output() const;
    char* update_output();

    char* last_output() const;
    void set_last_output(char*);
private:
    const char* m_command;
    u32 m_interval;
    i32 m_signal;
    u32 m_time_since_last_updated_in_sec = 0;
    char* m_last_output = NULL;
};
