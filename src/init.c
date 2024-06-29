/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:07:16 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:33:32 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pm(t_cub3d *const cub3d)
{
	size_t	i;

	i = 0;
	while (i < (size_t)ft_lstsize(cub3d->map2))
	{
		ft_printf("%s\n", ll_nod(cub3d->map2, i)->content);
		i++;
	}
}

int	init_cub3d(t_cub3d *const cub3d)
{
	if (init_mlx(cub3d))
		return (1);
	if (map_init(cub3d))
		return (1);
	ft_printf("SUCCESSFULLY VALIDATED\n");
	pm(cub3d);
	hook_init(cub3d);
	return (0);
}
