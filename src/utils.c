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
    return (c == ' ' \
        || c == '\t' \
        || c == '\n' \
        || c == '\v' \
        || c == '\f' \
        || c == '\r');
}

size_t  arrlen(void **arr)
{
	size_t	c;

	c = 0;
	while (arr[c])
		c++;
	return (c);
}

void    free_2d(void **ptr)
{
	size_t	c;

	c = 0;
	while (ptr[c])
    {
        free(ptr[c]);
		c++;
    }
    free(ptr);
	return ;
}