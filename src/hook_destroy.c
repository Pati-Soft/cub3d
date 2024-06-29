/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:12:02 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 14:46:30 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_the_textures(t_cub3d *const cub3d)
{
	t_list	*texture;
	int		i;

	i = 0;
	texture = cub3d->textures_success;
	while (texture)
	{
		if (texture)
			ft_printf("Destroying texture %d &%p\n", i, texture->content);
		mlx_destroy_image(cub3d->mlx, texture->content);
		texture = texture->next;
		i++;
	}
	if (cub3d->screen_buffer.img)
		mlx_destroy_image(cub3d->mlx, cub3d->screen_buffer.img);
	ft_printf("Destroyed screen buffer &%p\n", cub3d->screen_buffer.img);
	ft_lstclear(&cub3d->textures_success, void_fun);
}

void	destroy_map(t_list *map)
{
	ft_lstclear(&map, free);
}

void	dealloc_cub3d(t_cub3d *const cub3d)
{
	destroy_map(cub3d->map2);
	destroy_the_textures(cub3d);
	ft_printf("Window destroyed: %d\n",
		(mlx_destroy_window(cub3d->mlx, cub3d->win_mlx)));
}

int	destroy_game(t_cub3d *const cub3d)
{
	dealloc_cub3d(cub3d);
	printf("exitting\n");
	exit(0);
	return (0);
}
