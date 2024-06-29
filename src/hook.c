/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:42:58 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:20:06 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int const keycode, t_cub3d *const cub3d)
{
	if (keycode == MLX_KEY_ESC || keycode == MLX_KEY_Q)
		destroy_game(cub3d);
	if (keycode == MLX_KEY_W)
		cub3d->player.keys[KEY_W_IDX] = 1;
	if (keycode == MLX_KEY_A)
		cub3d->player.keys[KEY_A_IDX] = 1;
	if (keycode == MLX_KEY_S)
		cub3d->player.keys[KEY_S_IDX] = 1;
	if (keycode == MLX_KEY_D)
		cub3d->player.keys[KEY_D_IDX] = 1;
	if (keycode == MLX_KEY_LARROW)
		cub3d->player.keys[KEY_LARROW_IDX] = 1;
	if (keycode == MLX_KEY_RARROW)
		cub3d->player.keys[KEY_RARROW_IDX] = 1;
	return (0);
}

int	key_release(int const keycode, t_cub3d *const cub3d)
{
	if (keycode == MLX_KEY_W)
		cub3d->player.keys[KEY_W_IDX] = 0;
	if (keycode == MLX_KEY_A)
		cub3d->player.keys[KEY_A_IDX] = 0;
	if (keycode == MLX_KEY_S)
		cub3d->player.keys[KEY_S_IDX] = 0;
	if (keycode == MLX_KEY_D)
		cub3d->player.keys[KEY_D_IDX] = 0;
	if (keycode == MLX_KEY_LARROW)
		cub3d->player.keys[KEY_LARROW_IDX] = 0;
	if (keycode == MLX_KEY_RARROW)
		cub3d->player.keys[KEY_RARROW_IDX] = 0;
	return (0);
}

void	ft_move(t_cub3d *const cub3d)
{
	if (cub3d->player.keys[KEY_W_IDX])
		key_w(cub3d);
	if (cub3d->player.keys[KEY_A_IDX])
		key_a(cub3d);
	if (cub3d->player.keys[KEY_S_IDX])
		key_s(cub3d);
	if (cub3d->player.keys[KEY_D_IDX])
		key_d(cub3d);
	if (cub3d->player.keys[KEY_LARROW_IDX])
		key_left(cub3d);
	if (cub3d->player.keys[KEY_RARROW_IDX])
		key_right(cub3d);
}

int	ft_player_move(t_cub3d *const cub3d)
{
	ft_move(cub3d);
	return (0);
}

int	loop(void *const param)
{
	t_cub3d *const	cub3d = (t_cub3d *)param;

	ft_fill_floor_and_ceiling(cub3d);
	ft_player_move(cub3d);
	ft_ray_casting(cub3d);
	mlx_put_image_to_window(\
		cub3d->mlx, cub3d->win_mlx, cub3d->screen_buffer.img, 0, 0);
	return (0);
}
