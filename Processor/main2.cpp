

#define DEFINE_CMD_( cmd, def ) cmd_##cmd,

enum cmd
{  
cmd_MaxCmdError = -1,
#include "cmd_list.c"
cmd_MaxCmdNum
};

#undef DEFINE_CMD_

const int NMAX = 1000, CMD_MAX = 17;

struct Cmd_t
    {
    int         code;
    const char* name;
    };

const Cmd_t commands[] = {
    {cmd_nop,  "nop" },
    {cmd_push, "push"},
    {cmd_pop,  "pop" }
};

//------------------------------------------------------------------------

#define DEFINE_CMD_( cmd )                  \
    {                                       \
    commands[cmd_##cmd].code = cmd_##cmd;   \
    commands[cmd_##cmd].name = #cmd;        \
    }

void InitCommandTable (Cmd_t commands[])
{
#include "cmd_list.c"
}

#undef DEFINE_CMD_

#ifndef __cplusplus
typedef int bool;
#endif

