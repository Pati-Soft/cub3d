/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:44:15 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 17:24:17 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_meta_info(t_map_init *const map_init, t_cub3d *const cub3d)
{
	while (map_init->cont)
	{
		if (skip_empty_line(map_init))
			return (eerr(ERR_MISSING));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("trim: |%s|\n", map_init->buff);
		if (set_value(cub3d, map_init))
			return (free(map_init->buff), 1);
		free(map_init->buff);
	}
	return (0);
}

int	loop_map(t_map_init *const map_init, t_cub3d *const cub3d)
{
	if (skip_empty_line(map_init))
		return (eerr(ERR_MISSING));
	free(map_init->trim);
	map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	if (map_init->trim == NULL)
		return (free(map_init->buff), eerr(ERR_MALLOC));
	free(map_init->buff);
	map_init->buff = map_init->trim;
	ft_printf("validating row: %s\n", map_init->buff);
	if (validate_row_top(map_init->buff))
		return (free(map_init->buff), eerr(ERR_UNVALIDATABLE));
	if (validate_mid(map_init, cub3d))
		return (1);
	if (skip_empty_line(map_init) == 0)
		return (free(map_init->trim), free(map_init->buff), eerr(ERR_2MAP));
	return (0);
}

int	map_init(t_cub3d *const cub3d)
{
	t_map_init	map_init;

	ft_printf("initializing map\n");
	init_struct(&map_init);
	if (check_extension(cub3d->map_name, MAP_EXTENSION))
		return (eerr(EXAMPLE_ERR));
	if (open2(cub3d->map_name, O_RDONLY, &map_init.fd))
		return (perror(ERR_PREFIX), eerr(ERR_MAP_OPEN));
	if (loop_meta_info(&map_init, cub3d))
		return (close_err(map_init.fd), 1);
	if (loop_map(&map_init, cub3d))
		return (close_err(map_init.fd), clear_map(cub3d), 1);
	if (cub3d->player.posx == 0)
		return (close_err(map_init.fd), clear_map(cub3d), eerr(ERR_PLAYER));
	return (0);
}
