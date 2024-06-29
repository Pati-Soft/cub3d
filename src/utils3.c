/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:05:24 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:10:58 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	arrlen(void const *arr)
{
	size_t	c;

	c = 0;
	while (((void **)arr)[c])
		c++;
	return (c);
}

void	free_2d(void *ptr)
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

void	close_err(int const fd)
{
	if (close(fd) == -1)
		eerr(ERR_CLOSE_FD);
}

void	void_fun(void *content)
{
	(void)content;
}
