/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:06 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:08:24 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_surroundable_char(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
	return (*c == '0' || \
			*c == 'N' || \
			*c == 'S' || \
			*c == 'E' || \
			*c == 'W');
}

int	validate_top_char(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
	return (*c != '1' && \
			*c != ' ');
}

int	validate_edge_char(char const*const row)
{
	return (row[0] == '0' || \
			(row[ft_strlen(row) - 1] == '0'));
}

int	validate_row_top(char *const row)
{
	return (ft_strsome(row, validate_top_char, NULL));
}

t_char_type	get_char_type(char const c)
{
	t_char_type	stat;

	if (c == '1')
		stat = FRAME;
	else if (c == ' ')
		stat = SPACE;
	else if (c == '0' || \
			c == 'N' || \
			c == 'S' || \
			c == 'E' || \
			c == 'W')
		stat = SURROUNDABLE;
	else
		stat = INVALID_CHAR;
	return (stat);
}
