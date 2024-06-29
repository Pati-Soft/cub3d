/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 04:07:40 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:07:54 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_right(t_cub3d *const cub3d)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub3d->player.dirx;
	cub3d->player.dirx = cub3d->player.dirx * cos(-ROTATION_SPEED) - \
		cub3d->player.diry * sin(-ROTATION_SPEED);
	cub3d->player.diry = old_dirx * sin(-ROTATION_SPEED) + cub3d->player.diry
		* cos(-ROTATION_SPEED);
	old_planex = cub3d->ray.planex;
	cub3d->ray.planex = cub3d->ray.planex * cos(-ROTATION_SPEED) - \
		cub3d->ray.planey * sin(-ROTATION_SPEED);
	cub3d->ray.planey = old_planex * sin(-ROTATION_SPEED) + \
		cub3d->ray.planey * cos(-ROTATION_SPEED);
}

void	key_left(t_cub3d *const cub3d)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub3d->player.dirx;
	cub3d->player.dirx = cub3d->player.dirx * cos(ROTATION_SPEED) - \
		cub3d->player.diry * sin(ROTATION_SPEED);
	cub3d->player.diry = old_dirx * sin(ROTATION_SPEED) + cub3d->player.diry
		* cos(ROTATION_SPEED);
	old_planex = cub3d->ray.planex;
	cub3d->ray.planex = cub3d->ray.planex * cos(ROTATION_SPEED) - \
		cub3d->ray.planey * sin(ROTATION_SPEED);
	cub3d->ray.planey = old_planex * sin(ROTATION_SPEED) + cub3d->ray.planey
		* cos(ROTATION_SPEED);
}
