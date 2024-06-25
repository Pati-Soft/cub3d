#include "cub3d.h"

t_list const *ll_nod(t_list const *node, int index)
{
	if (index < 0)
		return (0);
	while (index-- > 0 && node->next)
		node = node->next;
	if (index > -1)
		return (0);
	return (node);
}

inline double rad_to_deg(double radians)
{
    return radians * (180.0 / M_PI);
}

inline double deg_to_rad(double degrees)
{
    return degrees * M_PI / 180.0;
}

int	x_isdigit(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return !(*curr >= '0' && *curr <= '9');
}

char	*ft_strrtrim(char const * const s1, char const * const set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

int	ft_strsome(char *s, int (*f)(unsigned int, char *, void *), void *pass)
{
	unsigned int	i;

	i = 0;
	if (!(*s) || !f)
		return (0);
	while (s[i])
	{
        if (f(i, &s[i], pass))
            return (1);
		i++;
	}
    return (0);
}


int err(char const *msg)
{
    while (*msg) write(2, msg++, 1);
    return (1);
}

int eerr(char const * const msg)
{
    err(ERR_PREFIX);
    return err(msg);
}

int     ft_isspace(int const c)
{
    return (c == ' ' \
        || c == '\t' \
        || c == '\n' \
        || c == '\v' \
        || c == '\f' \
        || c == '\r');
}

size_t  arrlen(void const *arr)
{
	size_t	c;

	c = 0;
	while (((void **)arr)[c])
		c++;
	return (c);
}

void    free_2d(void *ptr)
{
	size_t	c;

	c = 0;
	while (((void **)ptr)[c])
    {
        free(((void **)ptr)[c]);
		c++;
    }
    free(((void **)ptr));
	return ;
}
