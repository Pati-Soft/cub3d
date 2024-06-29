/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:18:19 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 17:55:36 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_character(char const c)
{
	if (c == NORTH_CHAR || c == SOUTH_CHAR
		|| c == EAST_CHAR || c == WEST_CHAR)
		return (1);
	return (0);
}

void	key_w(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.\
		dirx * MOVEMENT_SPEED))-> content)[(int)(cub3d->player.posy)] == '0'\
		|| is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx \
		+ cub3d->player.dirx * MOVEMENT_SPEED))->content)[(int)(cub3d->player.\
		posy)]))
		cub3d->player.posx += cub3d->player.dirx * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy + cub3d->player.diry * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->\
		content)[(int)(cub3d->player.posy + cub3d->player.diry * \
		MOVEMENT_SPEED)]))
		cub3d->player.posy += cub3d->player.diry * MOVEMENT_SPEED;
}

void	key_s(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.\
		dirx * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - \
		cub3d->player.dirx * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
		cub3d->player.posx -= cub3d->player.dirx * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy - cub3d->player.diry * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))[(\
		int)(cub3d->player.posy - cub3d->player.diry * MOVEMENT_SPEED)]))
		cub3d->player.posy -= cub3d->player.diry * MOVEMENT_SPEED;
}

void	key_d(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.\
		diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + \
		cub3d->player.diry * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
		cub3d->player.posx += cub3d->player.diry * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy - cub3d->player.dirx * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))[(\
		int)(cub3d->player.posy - cub3d->player.dirx * MOVEMENT_SPEED)]))
		cub3d->player.posy -= cub3d->player.dirx * MOVEMENT_SPEED;
}

void	key_a(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.\
		diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - \
		cub3d->player.diry * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
		cub3d->player.posx -= cub3d->player.diry * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy + cub3d->player.dirx * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))[(\
		int)(cub3d->player.posy + cub3d->player.dirx * MOVEMENT_SPEED)]))
		cub3d->player.posy += cub3d->player.dirx * MOVEMENT_SPEED;
}
