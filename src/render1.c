/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:20:13 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/30 16:30:10 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_floor_and_ceiling(t_cub3d *const cub3d)
{
	int	i;
	int	n;

	i = -1;
	while (++i < cub3d->screen_buffer.height / 2)
	{
		n = -1;
		while (++n < cub3d->screen_buffer.width)
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = \
			cub3d->gradient[0];
	}
	while (++i < cub3d->screen_buffer.height)
	{
		n = -1;
		while (++n < cub3d->screen_buffer.width)
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = \
			cub3d->gradient[1];
	}
}

void	ft_draw_wall_texture(
	t_cub3d *const cub3d, int const x, int const tex_index)
{
	int			texy;

	while (cub3d->ray.drawstart < cub3d->ray.drawend)
	{
		texy = (int)cub3d->ray.texpos & (cub3d->resulation - 1);
		cub3d->ray.texpos += cub3d->ray.texstep;
		if (cub3d->textures[tex_index].addr[(cub3d->resulation * texy) + \
			cub3d->ray.tex_x] > 0)
			cub3d->screen_buffer.addr[(cub3d->ray.drawstart * \
			cub3d->screen_buffer.width) + x] = \
			cub3d->textures[tex_index].addr[(cub3d->resulation * texy) + \
			cub3d->ray.tex_x];
		cub3d->ray.drawstart++;
	}
}

void	ft_texture_helper(t_cub3d *const cub3d)
{
	double	wallx;

	if (cub3d->ray.side == 0)
		wallx = \
		cub3d->player.posy + cub3d->ray.perpwalldist * cub3d->ray.raydiry;
	else
		wallx = \
		cub3d->player.posx + cub3d->ray.perpwalldist * cub3d->ray.raydirx;
	wallx -= floor(wallx);
	cub3d->ray.tex_x = (int)(wallx * (double)cub3d->resulation);
	if (cub3d->ray.side == 0 && cub3d->ray.raydirx > 0)
		cub3d->ray.tex_x = cub3d->resulation - cub3d->ray.tex_x - 1;
	if (cub3d->ray.side == 1 && cub3d->ray.raydiry < 0)
		cub3d->ray.tex_x = cub3d->resulation - cub3d->ray.tex_x - 1;
	cub3d->ray.texstep = 1.0 * cub3d->resulation / cub3d->ray.lineheight;
	cub3d->ray.texpos = (cub3d->ray.drawstart - cub3d->screen_buffer.height
			/ 2 + cub3d->ray.lineheight / 2) * cub3d->ray.texstep;
}

void	ft_draw_wall_side(t_cub3d *const cub3d, int const x)
{
	ft_texture_helper(cub3d);
	if (cub3d->ray.side == 0 && cub3d->ray.raydirx > 0)
		ft_draw_wall_texture(cub3d, x, 2);
	else if (cub3d->ray.side == 0 && cub3d->ray.raydirx < 0)
		ft_draw_wall_texture(cub3d, x, 3);
	else if (cub3d->ray.side == 1 && cub3d->ray.raydiry > 0)
		ft_draw_wall_texture(cub3d, x, 1);
	else
		ft_draw_wall_texture(cub3d, x, 0);
}
