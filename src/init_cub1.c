/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:37:13 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/30 16:21:11 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_empty_line(t_map_init *const map_init)
{
	while ("false")
	{
		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL)
			return (1);
		map_init->trim = ft_strtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (free(map_init->buff), eerr(ERR_MALLOC));
		if (*map_init->trim != '\0')
			return (0);
		free(map_init->buff);
		map_init->buff = NULL;
		free(map_init->trim);
		map_init->trim = NULL;
	}
	return (1);
}

void	init_struct(t_map_init *dest)
{
	*dest = (t_map_init){
		.lengths_key = \
			{[NO] = 2, [SO] = 2, [WE] = 2, [EA] = 2, [F] = 1, [C] = 1},
		.match_index = \
			{[F] = FLOOR, [C] = CEILING,
	[NO] = NORTH, [SO] = SOUTH, [WE] = WEST, [EA] = EAST},
		.match_types = \
			{[F] = 0, [C] = 0, [NO] = 1, [SO] = 1, [WE] = 1, [EA] = 1},
		.override = {0},
		.cont = 1,
		.meta_ct = IMAGE_COUNT + COLOR_COUNT,
		.meta_funcs = {
	[0] = set_color,
	[1] = set_texture,
	},
	};
}

int	check_extension(char const*const path, char const*const ext)
{
	if (ft_strlen(path) < 4 || ft_strncmp(ext,
			path + (ft_strlen(path) - 4), 4))
		return (1);
	return (0);
}

t_key	get_key(char const*const buff)
{
	if (!ft_strncmp(TEXT_NO, buff, 2))
		return (NO);
	if (!ft_strncmp(TEXT_SO, buff, 2))
		return (SO);
	if (!ft_strncmp(TEXT_WE, buff, 2))
		return (WE);
	if (!ft_strncmp(TEXT_EA, buff, 2))
		return (EA);
	if (!ft_strncmp(TEXT_F, buff, 1))
		return (F);
	if (!ft_strncmp(TEXT_C, buff, 1))
		return (C);
	return (KEY_END);
}
