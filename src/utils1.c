/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:05:30 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:10:53 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rad_to_deg(double radians)
{
	return (radians * (180.0 / M_PI));
}

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

t_return	err(char const *msg)
{
	while (*msg)
		write(2, msg++, 1);
	return (FAILURE);
}

t_return	eerr(char const*const msg)
{
	err(ERR_PREFIX);
	return (err(msg));
}

// cause `if ((fd = open(path, flags)) == -1)` is forbidden
int	open2(char const*const path, int const flags, int *const fd)
{
	*fd = open(path, flags);
	if (*fd == -1)
		return (1);
	return (0);
}
