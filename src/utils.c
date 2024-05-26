#include "cub3d.h"

int err(char *msg)
{
    while (*msg) write(2, msg++, 1);
    return (1);
}

int eerr(char *msg)
{
    err(ERR_PREFIX);
    return err(msg);
}

int     ft_isspace(int c)
{
    return (c == ' ');
}