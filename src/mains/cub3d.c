/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:10:27 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:43:13 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((destructor)) void	destructor(void)
{
	printf("Destructor called\n");
	system("leaks cub3d");
}

void	init_variable(t_cub3d *const cub3d, int argc, char const *argv[])
{
	*((char **)&cub3d->map_name) = (char *)argv[argc - 1];
	cub3d->ray.deltadistx = 0;
	cub3d->ray.deltadisty = 0;
	cub3d->ray.perpwalldist = 0;
	cub3d->ray.stepx = 0;
	cub3d->ray.stepy = 0;
	cub3d->ray.sidedistx = 0;
	cub3d->ray.sidedisty = 0;
	cub3d->ray.map_x = 0;
	cub3d->ray.map_y = 0;
	cub3d->ray.side = 0;
	cub3d->ray.wall = 0;
	cub3d->ray.raydirx = 0;
	cub3d->ray.raydiry = 0;
}

int	main(int argc, char const *argv[])
{
	t_cub3d *const	cub3d = &(t_cub3d){0};

	init_variable(cub3d, argc, argv);
	if (argc != 2)
		return (eerr(ERR_ARGC));
	if (init_cub3d(cub3d))
		return (dealloc_cub3d(cub3d), 1);
	mlx_loop(cub3d->mlx);
	return (0);
}
