/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:05:17 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/30 16:14:28 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strrtrim(char const*const s1, char const*const set)
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

t_list	*ll_nod(t_list const *node, int index)
{
	if (index < 0)
		return (0);
	while (index-- > 0 && node->next)
		node = node->next;
	if (index > -1)
		return (0);
	return ((t_list *)node);
}

int	x_isdigit(unsigned int idx, char *curr, void *param)
{
	(void)idx;
	(void)param;
	return (!(*curr >= '0' && *curr <= '9'));
}

int	ft_isspace(int const c)
{
	return (c == ' ' \
		|| c == '\t' \
		|| c == '\n' \
		|| c == '\v' \
		|| c == '\f' \
		|| c == '\r');
}
