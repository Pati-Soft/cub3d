#include "cub3d.h"

int err(char *msg)
{
    while (*msg) write(2, msg++, 1);
    return (1);
}

int     ft_isspace(int c)
{
    return (c == '\f' || c == '\n' || c == '\r' \
    || c == '\t' || c == '\v' || c == ' ');
}