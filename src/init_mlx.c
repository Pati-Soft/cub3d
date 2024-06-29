/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:38:56 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:09:29 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_init(t_cub3d *const cub3d)
{
	mlx_do_key_autorepeatoff(cub3d->mlx);
	ft_printf("[LOG]: init event listeners.\n");
	mlx_hook(cub3d->win_mlx, ON_DESTROY, 0, destroy_game, cub3d);
	mlx_hook(cub3d->win_mlx, 2, (1L << 0), key_press, cub3d);
	mlx_hook(cub3d->win_mlx, 3, (1L << 1), key_release, cub3d);
	cub3d->resulation = cub3d->textures[0].width;
	printf("resulation: %d\n", cub3d->resulation);
	mlx_loop_hook(cub3d->mlx, loop, cub3d);
}

int	screen_buffer_init(t_cub3d *const cub3d, int screen_x, int screen_y)
{
	cub3d->screen_buffer.img = mlx_new_image(cub3d->mlx, screen_x, screen_y);
	if (cub3d->screen_buffer.img == NULL)
		return (1);
	cub3d->screen_buffer.width = screen_x;
	cub3d->screen_buffer.height = screen_y;
	cub3d->screen_buffer.addr = (int *)mlx_get_data_addr(
			cub3d->screen_buffer.img,
			&cub3d->screen_buffer.bits_per_pixel,
			&cub3d->screen_buffer.size_line,
			&cub3d->screen_buffer.endian);
	if (cub3d->screen_buffer.addr == NULL)
		return (1);
	printf("bitperpixel: %d, size_line: %d, endian: %d\n",
		cub3d->screen_buffer.bits_per_pixel,
		cub3d->screen_buffer.size_line,
		cub3d->screen_buffer.endian);
	return (0);
}

// mlx_get_screen_size(cub3d->mlx, &screen_x, &screen_y);
int	init_mlx(t_cub3d *const cub3d)
{
	int				screen_x;
	int				screen_y;

	cub3d->mlx = mlx_init();
	if (cub3d->mlx == NULL)
		return (1);
	screen_x = WIN_WIDTH;
	screen_y = WIN_HEIGHT;
	printf("screen: %d %d\n", screen_x, screen_y);
	cub3d->win_mlx = \
		mlx_new_window(cub3d->mlx, screen_x, screen_y, cub3d->map_name);
	if (cub3d->win_mlx == NULL)
		return (1);
	if (screen_buffer_init(cub3d, screen_x, screen_y))
		return (1);
	return (0);
}
