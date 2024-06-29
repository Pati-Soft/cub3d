/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:40:13 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 20:24:22 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_map(t_cub3d *const cub3d)
{
	ft_lstclear(&cub3d->map2, free);
}

int	check_relative(const size_t prev_len, char const*const row,
	char const*const prev, size_t const i)
{
	t_char_type		curr;
	t_char_type		v_prev;
	t_char_type		h_next;

	curr = get_char_type(row[i]);
	h_next = get_char_type(row[i + 1]);
	if ((prev_len - 1) < i)
		v_prev = INVALID_CHAR;
	else
		v_prev = get_char_type(prev[i]);
	if (curr == INVALID_CHAR)
		return (eerr(ERR_UNVALIDATABLE2));
	{
		if (curr == SPACE)
			if ((h_next == SURROUNDABLE) || (v_prev == SURROUNDABLE))
				return (eerr(ERR_UNVALIDATABLE3));
		if (curr == SURROUNDABLE)
			if (h_next == SPACE || v_prev == SPACE || v_prev == INVALID_CHAR)
				return (eerr(ERR_UNVALIDATABLE4));
	}
	return (0);
}

int	player_detected(t_cub3d *const cub3d, char *const row, size_t i)
{
	if (cub3d->player.posx)
		return (eerr(ERR_MULTIPLAYER));
	cub3d->player.posy = i;
	cub3d->player.posx = ft_lstsize(cub3d->map2) - 0;
	cub3d->player.direction = (int const [UINT8_MAX]){\
		['N'] = DIR_N, ['E'] = DIR_E, ['S'] = DIR_S, ['W'] = DIR_W} \
		[(int)row[i]];
	cub3d->player.posy += 0.5;
	cub3d->player.posx += 0.5;
	cub3d->player.dirx = cos(deg_to_rad(cub3d->player.direction));
	cub3d->player.diry = sin(deg_to_rad(cub3d->player.direction));
	cub3d->ray.planex = cub3d->player.diry * FOV;
	cub3d->ray.planey = -cub3d->player.dirx * FOV;
	printf("player: x: %lf, y: %lf, direction: %d\n", cub3d->player.posx,
		cub3d->player.posy, cub3d->player.direction);
	row[i] = '0';
	return (0);
}

int	validate_row_mid(char *const row, char *const prev, t_cub3d *const cub3d)
{
	const size_t	prev_len = ft_strlen(prev);
	size_t			i;

	if (validate_edge_char(row))
		return (eerr(ERR_UNVALIDATABLE1));
	i = 0;
	while (row[++i + 1])
	{
		if ((row[i] == 'N' || row[i] == 'S' || row[i] == 'E' || row[i] == 'W'))
			if (player_detected(cub3d, row, i))
				return (1);
		if (check_relative(prev_len, row, prev, i))
			return (1);
	}
	if (prev_len > ++i)
		if (ft_strsome(prev + i, is_surroundable_char, NULL))
			return (eerr(ERR_UNVALIDATABLE5));
	return (0);
}

int	validate_mid(t_map_init *const map_init, t_cub3d *const cub3d)
{
	while (1)
	{
		ft_lstadd_back(&cub3d->map2, ft_lstnew(map_init->buff));
		map_init->prev = map_init->buff;
		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL || *map_init->buff == '\n')
		{
			if (validate_row_top(map_init->prev))
				return (eerr(ERR_UNVALIDATABLE));
			break ;
		}
		map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (free(map_init->buff), eerr(ERR_MALLOC));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("validating row: %s\n", map_init->buff);
		if (validate_row_mid(map_init->buff, map_init->prev, cub3d))
			return (free(map_init->buff), 1);
	}
	return (0);
}
