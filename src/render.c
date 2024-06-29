/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:29:02 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 17:59:37 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_direction(t_cub3d *const cub3d, int const x)
{
	if (cub3d->ray.raydirx < 0)
	{
		cub3d->ray.stepx = -1;
		cub3d->ray.sidedistx = (cub3d->player.posx - cub3d->ray.map_y)
			* cub3d->ray.deltadistx;
	}
	else
	{
		cub3d->ray.stepx = 1;
		cub3d->ray.sidedistx = (cub3d->ray.map_y + 1.0 - cub3d->player.posx)
			* cub3d->ray.deltadistx;
	}
	if (cub3d->ray.raydiry < 0)
	{
		cub3d->ray.stepy = -1;
		cub3d->ray.sidedisty = (cub3d->player.posy - cub3d->ray.map_x)
			* cub3d->ray.deltadisty;
	}
	else
	{
		cub3d->ray.stepy = 1;
		cub3d->ray.sidedisty = (cub3d->ray.map_x + 1.0 - cub3d->player.posy)
			* cub3d->ray.deltadisty;
	}
	ft_wallhit(cub3d, x);
}

void	ft_wallhit(t_cub3d *const cub3d, int const x)
{
	cub3d->ray.wall = 0;
	while (!cub3d->ray.wall)
	{
		if (cub3d->ray.sidedistx < cub3d->ray.sidedisty)
		{
			cub3d->ray.sidedistx += cub3d->ray.deltadistx;
			cub3d->ray.map_y += cub3d->ray.stepx;
			cub3d->ray.side = 0;
		}
		else
		{
			cub3d->ray.sidedisty += cub3d->ray.deltadisty;
			cub3d->ray.map_x += cub3d->ray.stepy;
			cub3d->ray.side = 1;
		}
		if (((char *)ll_nod(cub3d->map2, cub3d->ray.map_y)->content) \
			[cub3d->ray.map_x] == WALL_CHAR)
			cub3d->ray.wall = 1;
	}
	ft_raydist(cub3d, x);
}

void	ft_raydist(t_cub3d *const cub3d, int const x)
{
	if (cub3d->ray.side == 0)
		cub3d->ray.perpwalldist = cub3d->ray.sidedistx - cub3d->ray.deltadistx;
	else
		cub3d->ray.perpwalldist = cub3d->ray.sidedisty - cub3d->ray.deltadisty;
	if (cub3d->ray.perpwalldist < 0.001)
		cub3d->ray.perpwalldist += 0.001;
	cub3d->ray.lineheight = \
		(int)(cub3d->screen_buffer.height / cub3d->ray.perpwalldist * 2);
	cub3d->ray.drawstart = \
		-cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
	if (cub3d->ray.drawstart < 0)
		cub3d->ray.drawstart = 0;
	cub3d->ray.drawend = \
		cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
	if (cub3d->ray.drawend >= cub3d->screen_buffer.height)
		cub3d->ray.drawend = cub3d->screen_buffer.height - 1;
	ft_draw_wall_side(cub3d, x);
}

/*
cub3d->ray.camerax = (double)x / (cub3d->screen_buffer.width - 1);
// Ekran genişliğine orantılı
*/

/*
cub3d->ray.raydirx = cub3d->player.dirx+ 
(cub3d->ray.planex * (cub3d->ray.camerax - 0.5) * 2); // Orta noktayı 0.5 yapar
*/

/*
cub3d->ray.raydiry = cub3d->player.diry + \
(cub3d->ray.planey * (cub3d->ray.camerax - 0.5) * 2); // Orta noktayı 0.5 yapar
*/

void	ft_ray_casting(t_cub3d *const cub3d)
{
	int			x;

	x = 0;
	while (x < cub3d->screen_buffer.width)
	{
		cub3d->ray.camerax = (double)x / (cub3d->screen_buffer.width - 1);
		cub3d->ray.raydirx = (cub3d->player.dirx + (cub3d->ray.planex * \
			(cub3d->ray.camerax - 0.5) * 2));
		cub3d->ray.raydiry = (cub3d->player.diry + (cub3d->ray.planey * \
			(cub3d->ray.camerax - 0.5) * 2));
		cub3d->ray.map_y = (int)cub3d->player.posx;
		cub3d->ray.map_x = (int)cub3d->player.posy;
		cub3d->ray.deltadistx = fabs(1 / cub3d->ray.raydirx);
		cub3d->ray.deltadisty = fabs(1 / cub3d->ray.raydiry);
		ft_direction(cub3d, x);
		x++;
	}
}
